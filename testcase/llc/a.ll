; ModuleID = 'a.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "i0-pc-linux-gnu"

; Function Attrs: nounwind uwtable
define void @add() #0 {
  %1 = load i64* inttoptr (i64 1280 to i64*), align 256, !tbaa !1
  %2 = load i64* inttoptr (i64 1024 to i64*), align 1024, !tbaa !1
  %3 = add nsw i64 %2, %1
  store i64 %3, i64* inttoptr (i64 2048 to i64*), align 2048, !tbaa !1
  ret void
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.5-1ubuntu1 (trunk) (based on LLVM 3.5)"}
!1 = metadata !{metadata !2, metadata !2, i64 0}
!2 = metadata !{metadata !"long", metadata !3, i64 0}
!3 = metadata !{metadata !"omnipotent char", metadata !4, i64 0}
!4 = metadata !{metadata !"Simple C/C++ TBAA"}
