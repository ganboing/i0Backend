; ModuleID = 'complex32.bc'
target datalayout = "E-m:m-p:32:32-i8:8:32-i16:16:32-i64:64-n32-S64"
target triple = "mips-unknown-linux-gnu"

; Function Attrs: nounwind optsize
define void @test() #0 {
  %1 = load i32* inttoptr (i32 128 to i32*), align 128, !tbaa !1
  %2 = icmp sgt i32 %1, 0
  br i1 %2, label %.lr.ph, label %7

.lr.ph:                                           ; preds = %0
  %.promoted = load i32* inttoptr (i32 64 to i32*), align 64, !tbaa !1
  br label %3

; <label>:3                                       ; preds = %3, %.lr.ph
  %4 = phi i32 [ %.promoted, %.lr.ph ], [ %5, %3 ]
  %i.01 = phi i32 [ 0, %.lr.ph ], [ %6, %3 ]
  %5 = mul nsw i32 %4, %i.01
  %6 = add nsw i32 %i.01, 1
  %exitcond = icmp eq i32 %6, %1
  br i1 %exitcond, label %._crit_edge, label %3

._crit_edge:                                      ; preds = %3
  store i32 %5, i32* inttoptr (i32 64 to i32*), align 64, !tbaa !1
  br label %7

; <label>:7                                       ; preds = %._crit_edge, %0
  ret void
}

attributes #0 = { nounwind optsize "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.5-1ubuntu1 (trunk) (based on LLVM 3.5)"}
!1 = metadata !{metadata !2, metadata !2, i64 0}
!2 = metadata !{metadata !"int", metadata !3, i64 0}
!3 = metadata !{metadata !"omnipotent char", metadata !4, i64 0}
!4 = metadata !{metadata !"Simple C/C++ TBAA"}
