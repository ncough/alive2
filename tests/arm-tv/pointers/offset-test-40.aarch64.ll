; ModuleID = 'foo.c'
source_filename = "foo.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx13.0.0"

%struct.s = type { i16, i16, i16, i16, i64, i32, i16, i64 }

; Function Attrs: mustprogress nofree norecurse nosync nounwind ssp uwtable willreturn
define void @f(%struct.s* nocapture %0) local_unnamed_addr #0 {
  %2 = getelementptr inbounds %struct.s, %struct.s* %0, i64 0, i32 3
  %3 = load i16, i16* %2, align 2
  %4 = zext i16 %3 to i32
  %5 = zext i16 %3 to i64
  %6 = getelementptr inbounds %struct.s, %struct.s* %0, i64 0, i32 4
  store i64 %5, i64* %6, align 8
  %7 = getelementptr inbounds %struct.s, %struct.s* %0, i64 0, i32 0
  %8 = load i16, i16* %7, align 8
  %9 = zext i16 %8 to i32
  %10 = add nuw nsw i32 %9, %4
  %11 = zext i32 %10 to i64
  %12 = getelementptr inbounds %struct.s, %struct.s* %0, i64 0, i32 7
  store i64 %11, i64* %12, align 8
  %13 = trunc i32 %10 to i16
  %14 = getelementptr inbounds %struct.s, %struct.s* %0, i64 0, i32 6
  store i16 %13, i16* %14, align 4
  %15 = getelementptr inbounds %struct.s, %struct.s* %0, i64 0, i32 1
  store i16 %13, i16* %15, align 2
  %16 = add nuw nsw i32 %10, %4
  %17 = trunc i32 %16 to i16
  store i16 %17, i16* %2, align 2
  %18 = getelementptr inbounds %struct.s, %struct.s* %0, i64 0, i32 5
  store i32 %16, i32* %18, align 8
  store i16 %17, i16* %7, align 8
  ret void
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind ssp uwtable willreturn "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.5a,+zcm,+zcz" }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8}
!llvm.ident = !{!9}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 13, i32 1]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 1, !"branch-target-enforcement", i32 0}
!3 = !{i32 1, !"sign-return-address", i32 0}
!4 = !{i32 1, !"sign-return-address-all", i32 0}
!5 = !{i32 1, !"sign-return-address-with-bkey", i32 0}
!6 = !{i32 7, !"PIC Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 1}
!9 = !{!"Apple clang version 14.0.0 (clang-1400.0.29.202)"}
