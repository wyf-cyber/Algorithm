`timescale 1ns / 1ps
`define dm_word 3'b000
`define dm_halfword 3'b001
`define dm_halfword_unsigned 3'b010
`define dm_byte 3'b011
`define dm_byte_unsigned 3'b100

module DM(
input				clk,   //100MHZ CLK
input 				DMWr,  // write signal
input [5:0]			addr,  // 操作地址
input [31:0]		din,   // 写入的数据
input [2:0]			DMType,// 操作数据的类型 
output reg [31:0]	dout   // 输出的数据，读取结果
    );
reg[7:0] dmem[6:0];  // 初始化2的7次方(128)个字节的存储空间
always @ (posedge clk) begin 
    if(DMWr) begin
        // write signal is valid
        // 存储时不考虑符号扩展，只存数据
        case(DMType)
            `dm_byte:
                dmem[addr] <= din[7:0];
            `dm_halfword: begin
                dmem[addr] <= din[7:0];
                dmem[addr+1] <= din[15:8];
            end
            `dm_word: begin
                dmem[addr] <= din[7:0];
                dmem[addr+1] <= din[15:8];
                dmem[addr+2] <= din[23:16];
                dmem[addr+3] <= din[31:24];
            end
            default: begin
                dmem[addr] <= din[7:0];
                dmem[addr+1] <= din[15:8];
                dmem[addr+2] <= din[23:16];
                dmem[addr+3] <= din[31:24];
            end
        endcase 
    end else  begin 
        // null
    end 
    // read data
    // 所有数据以补码形式存储和读取
    case(DMType) 
        `dm_byte: 
            dout = {{24{dmem[addr][7]}},dmem[addr][7:0]};
        `dm_byte_unsigned:
            dout = {{24{1'b0}},dmem[addr][7:0]};
        `dm_halfword:
            dout = {{16{dmem[addr+1][7]}},dmem[addr+1][7:0],dmem[addr][7:0]};
        `dm_halfword_unsigned:
            dout = {{16{1'b0}},dmem[addr+1][7:0],dmem[addr][7:0]};
        `dm_word:
            dout = {dmem[addr+3][7:0],dmem[addr+2][7:0],dmem[addr+1][7:0],dmem[addr][7:0]};
        default:
            dout = {dmem[addr+3][7:0],dmem[addr+2][7:0],dmem[addr+1][7:0],dmem[addr][7:0]};
    endcase
end 
endmodule
