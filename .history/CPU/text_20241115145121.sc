class MyOperatorsTwo extends Module {
  val io = IO(new Bundle {
    val in      = Input(UInt(4.W))
    val out_mux = Output(UInt(4.W))
    val out_cat = Output(UInt(4.W))
  })

  val s = true.B
  io.out_mux := Mux(s, 3.U, 0.U) // should return 3.U, since s is true
  io.out_cat := Cat(2.U, 1.U)    // concatenates 2 (b10) with 1 (b1) to give 5 (101)
}

println(getVerilog(new MyOperatorsTwo))

test(new MyOperatorsTwo) { c =>
  c.io.out_mux.expect(3.U)
  c.io.out_cat.expect(5.U)
}
println("SUCCESS!!")