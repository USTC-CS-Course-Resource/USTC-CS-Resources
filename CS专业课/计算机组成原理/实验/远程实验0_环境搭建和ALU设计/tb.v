module tb();
reg [2:0] a,b;
reg [1:0] fun;   
alu     alu(
.a      (a),
.b      (b),
.fun    (fun),
.s      (),
.y      ()
);
initial
begin
    repeat(20)
    begin
        a = $random % 8;
        b = $random % 8;
        fun = $random % 4;
        #20;
    end
    $stop;
end
endmodule