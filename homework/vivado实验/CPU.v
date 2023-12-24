`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/05 09:38:52
// Design Name: 
// Module Name: SCPU_TOP
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////
//000000b3 00108093 00000133 00210113 000001b3 00318193 001020a3 00202123 003021a3 00102203 00202283 00302303;
`define WDSel_FromALU 2'b00
`define WDSel_FromMEM 2'b01

module SCPU_TOP(
    input clk,  //100MHZ CLK
    input rstn,  //reset signal
    input [15:0] sw_i, //sw_i[15]---sw_i[0] 
    output [7:0] disp_an_o, //8位数码管位选
    output [7:0] disp_seg_o //数码管8段数据
    );
    
    reg[31:0] clkdiv;
    wire Clk_CPU;
    //分频
    always @(posedge clk or negedge rstn) begin
        if(!rstn) clkdiv <= 0;
        else clkdiv <= clkdiv + 1'b1; 
    end
    //sw_i[15]选择慢速模式或快速模式
    assign Clk_CPU = (sw_i[15])? clkdiv[27] : clkdiv[25];
    
    reg[4:0]rom_addr;
    wire[31:0] inst_in;

    //rom每周期地址顺序取数
    always @(posedge Clk_CPU or negedge rstn) begin
        if(!rstn) begin rom_addr = 5'b0; end
        else begin
            if (rom_addr < 12) begin
                if(sw_i[1]==1'b0)begin
                    rom_addr = rom_addr + 1'b1;
                end
            end
            else  
                rom_addr = 5'b00000; 
            end
        end

    //从coe文件中取指令
    dist_mem_gen_cz2 u_im(
        .a(rom_addr),
        .spo(inst_in)
    );
    
    reg[6:0] Op;
    reg[6:0] Funct7;
    reg[2:0] Funct3;
    reg[11:0] iimm;
    reg[11:0] simm;
    wire[1:0] WDSel;
    wire[5:0] EXTOp;
    reg[4:0]rs1;
    reg[4:0]rs2;
    reg[4:0]rd;
    //Decode
    always@(*)begin
        Op = inst_in[6:0];  // op
        Funct7 = inst_in[31:25]; // funct7
        Funct3 = inst_in[14:12]; // funct3
        rs1 = inst_in[19:15];  // rs1
        rs2 = inst_in[24:20];  // rs2
        rd = inst_in[11:7];  // rd
        iimm=inst_in[31:20];//addi 指令立即数，lw指令立即数
        simm={inst_in[31:25],inst_in[11:7]}; //sw指令立即数  
    end
    
    wire ALUSrc;
    wire[4:0] ALUOp;
    wire[31:0]RD1;
    wire[31:0]RD2;
    reg signed[31:0]WD;
    wire RegWrite;
    wire [2:0] DMType;
    wire MemWrite;
    wire[31:0] 	immout;
    //生成控制信号
    ctrl u_ctrl(
        .Op(Op),  //opcode
        .Funct7(Funct7),  //funct7 
        .Funct3(Funct3),    // funct3 
        .RegWrite(RegWrite), // control signal for register write
        .MemWrite(MemWrite), // control signal for memory write
        .EXTOp(EXTOp),    // control signal to signed extension
        .ALUOp(ALUOp),    // ALU opertion
        //output [2:0] NPCOp,    // next pc operation
        .ALUSrc(ALUSrc),   // ALU source for b
        .DMType(DMType), //dm r/w type
        .WDSel(WDSel)    // (register) write data selection  (MemtoReg)
    );
    //符号拓展
    ext u_ext(
        .iimm(iimm),  //instr[31:20], 12 bits
        .simm(simm), //instr[31:25, 11:7], 12 bits
        .EXTOp(EXTOp),
        .immout(immout)
    );
    
    reg[31:0]reg_data;
    reg[4:0] reg_addr;
    
     //寄存器每周期顺序取数
    always@(posedge Clk_CPU or negedge rstn)begin
        if (!rstn) begin reg_addr=5'b0;end 
        else if(sw_i[13] == 1'b1)begin
            if(reg_addr < 9)begin 
                reg_data={{3'b0},reg_addr[4:0],u_rf.rf[reg_addr][23:0]};
                reg_addr=reg_addr + 1;end
            else begin
                reg_addr = 5'b00000;
            end
        end 
    end
    
    //寄存器修改和取数
    rf u_rf(
        .clk(Clk_CPU),
        .rstn(rstn),
        .RFWr(RegWrite),
        .sw_i(sw_i[15:0]),
        .A1(rs1),
        .A2(rs2),
        .A3(rd),
        .WD(WD),
        .RD1(RD1),
        .RD2(RD2)
    );
    //alu
    wire signed [31:0] A;
    wire signed[31:0] B ;
    wire Zero;
    wire signed[31:0] aluout;

    //alu_mux
    assign A = RD1;
    assign B = (ALUSrc == 1'b1)?immout:RD2;
    //alu计算地址和算术式
    alu u_alu(
        .A(A),
        .B(B),
        .ALUOp(ALUOp),
        .C(aluout),
        .Zero(Zero)
    );
      
    reg [4:0] dmem_addr;
    reg [31:0]dmem_data;
    reg [31:0]dm_din;
    reg [5:0]dm_addr;
    wire[31:0] dm_out;
    
    //循环显示前16个dm内容
    always @(posedge Clk_CPU or negedge rstn) begin
        if(!rstn) begin  
            dmem_addr = 5'b00000;
            dmem_data = 32'hFFFFFFFF; end
        else if(sw_i[11] == 1'b1)begin
            dmem_addr = dmem_addr + 1'b1;
            dmem_data = {dmem_addr[3:0],{20'b0},u_dm.dmem[dmem_addr][7:0]};
            if(dmem_addr >= 5'b10000 )begin
                dmem_addr = 5'b00000;
                dmem_data = 32'hFFFFFFFF;end
        end
    end
    //修改数据存储
    dm u_dm(
        .clk(Clk_CPU),
        .DMWr(MemWrite),
        .addr(aluout),
        .din(RD2),
        .DMType(DMType),
        .dout(dm_out)
    );
    
    //wd_mux
    always @(*) begin
	   case(WDSel)
		  `WDSel_FromALU: WD <= aluout;
		  `WDSel_FromMEM: WD <= dm_out;
		  //`WDSel_FromPC: WD<=PC_out+4;
	   endcase
    end
    
    reg[31:0] display_data;
    //显示模块数据选择
    always @(sw_i) begin
        if(sw_i[0] == 0)begin
            case (sw_i[14:11])
                4'b1000 : display_data = inst_in;
                4'b0100 : display_data = reg_data;
                4'b0010 : display_data = aluout;
                4'b0001 : display_data = dmem_data;
            default: display_data = inst_in;
            endcase
        end
    end
    //显示模块例化
    seg7x16 u_seg7x16(
        .clk(clk),
        .rstn(rstn),
        .i_data(display_data),
        .disp_mode(sw_i[0]),
        .o_seg(disp_seg_o),
        .o_sel(disp_an_o)
    );
endmodule