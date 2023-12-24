`timescale 1ns / 1ps

module ctrl(
input [6:0] opcode,  //opcode
input [6:0] funct7,  //funct7 
input [2:0] funct3,    // funct3 
input Zero,
output RegWrite, // control signal for register write
output MemWrite, // control signal for memory write
output	[5:0] extendSrc,    // control signal to signed extension
output [4:0] ALUOp,    // ALU opertion
//output [2:0] NPCOp,    // next pc operation
output ALUSrc,   // ALU source for b
output [2:0] DMType, //dm r/w type
output MemtoReg    // (register) write data selection  (MemtoReg)

    );
    // instruction type signals
    reg rType, iType_L, iType_R, sType;         // 1 bit signal
    reg add, sub, lb, lh, lw, lbu, lhu, addi, sw, sb, sh; // 1 bit signal
    // control signals(temp)
    reg RegWrite_temp, MemWrite_temp, ALUSrc_temp, MemtoReg_temp;
    reg [5:0] extendSrc_temp = 6'b000000;
    reg [4:0] ALUOp_temp = 5'b00000;
    reg [2:0] DMType_temp = 3'b000; 

    // figure out the type of the instruction
    wire rType = ~opcode[6]&opcode[5]&opcode[4]&~opcode[3]&~opcode[2]&opcode[1]&opcode[0]; //011
    wire iType_L = ~opcode[6]&~opcode[5]&~opcode[4]&~opcode[3]&~opcode[2]&opcode[1]&opcode[0]; //0000011
    wire iType_R  = ~opcode[6]&~opcode[5]&opcode[4]&~opcode[3]&~opcode[2]&opcode[1]&opcode[0]; //0010011 
    wire sType = ~opcode[6]&opcode[5]&~opcode[4]&~opcode[3]&~opcode[2]&opcode[1]&opcode[0]; //0100011
    // figure out the instruction's name
    // R format
    wire add = rType&~funct7[6]&~funct7[5]&~funct7[4]&~funct7[3]&~funct7[2]&~funct7[1]&~funct7[0]&~funct3[2]&~funct3[1]&~funct3[0]; // add 0000000 000
    wire sub = rType&~funct7[6]&funct7[5]&~funct7[4]&~funct7[3]&~funct7[2]&~funct7[1]&~funct7[0]&~funct3[2]&~funct3[1]&~funct3[0]; // sub 0100000 000
    // I format
    wire lb = iType_L&~funct3[2]& ~funct3[1]& ~funct3[0]; //lb 000
    wire lh = iType_L&~funct3[2]& ~funct3[1]& funct3[0];  //lh 001
    wire lw = iType_L&~funct3[2]& funct3[1]& ~funct3[0];  //lw 010
    wire addi = iType_R& ~funct3[2]& ~funct3[1]& ~funct3[0]; // addi 000 func3
    // S format
    wire sw = sType& ~funct3[2]&funct3[1]&~funct3[0]; // sw 010
    wire sb = sType& ~funct3[2]& ~funct3[1]&~funct3[0];
    wire sh = sType& ~funct3[2]&~funct3[1]&funct3[0];
    
    // generate suitable control signals
    assign RegWrite_temp   = rType | iType_R|iType_L  ; // register write
    assign MemWrite_temp   = sType;              // memory write
    assign ALUSrc_temp     = iType_R | sType | iType_L ; // ALU B is from instruction immediate
    // MemtoReg_FromALU = 2'b00  MemtoReg_FromMEM = 2'b01
    assign MemtoReg_temp = iType_L ? 3'b00 : 3'b01; 
    
    // generate ALUOp
    //ALUOp_nop 5'b00000
    //ALUOp_lui 5'b00001
    //ALUOp_auipc 5'b00010
    //ALUOp_add 5'b00011
    // only have two cases:000 00-sub,000 11-add
    assign ALUOp_temp[0]= add  | addi | sType | iType_L ;
    assign ALUOp_temp[1]= add  | addi | sType | iType_L ;
    //操作指令生成常数扩展操作
    // s-01,i-10
    if(sType) 
    assign extendSrc_temp = 6'b000100;
    else if(iType_L | iType_R) 
    assign extendSrc = 6'b000010;
    else 
    assign extendSrc_temp = 6'b000000; 
    //根据具体S和i_L指令生成DataMem数据操作类型编码   
    // dm_word 3'b000
    //dm_halfword 3'b001
    //dm_halfword_unsigned 3'b010
    //dm_byte 3'b011
    //dm_byte_unsigned 3'b100
    assign DMType_temp[2]= lbu;
    assign DMType_temp[1]= lb | sb | lhu;
    assign DMType_temp[0]= lh | sh | lb | sb;

 
endmodule
