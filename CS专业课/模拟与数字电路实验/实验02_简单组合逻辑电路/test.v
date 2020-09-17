module test(	//模块名称
    input in,	//输入信号声明
    output out,	//输出信号声明
    output out_n);
    //可在此声明内部变量
    /*******以下为逻辑描述部分******/
    assign out = in;
    assign out_n = ~in;
    /*******逻辑描述部分结束******/
endmodule   //模块名结束关键词

