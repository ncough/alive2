define <1 x i64> @ctpop_v1i64(<1 x i64> %0) {
  %2 = call <1 x i64> @llvm.ctpop.v1i64(<1 x i64> %0)
  ret <1 x i64> %2
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare <1 x i64> @llvm.ctpop.v1i64(<1 x i64>) #0
