; ModuleID = 'complex.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind optsize uwtable
define void @test() #0 {
  %1 = load i32* inttoptr (i64 128 to i32*), align 128, !tbaa !1
  %2 = icmp sgt i32 %1, 0
  br i1 %2, label %.lr.ph, label %6

.lr.ph:                                           ; preds = %0
  %.promoted = load i64* inttoptr (i64 64 to i64*), align 64, !tbaa !5
  br label %3

; <label>:3                                       ; preds = %3, %.lr.ph
  %indvars.iv = phi i64 [ 0, %.lr.ph ], [ %indvars.iv.next, %3 ]
  %4 = phi i64 [ %.promoted, %.lr.ph ], [ %5, %3 ]
  %5 = mul nsw i64 %4, %indvars.iv
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
  %lftr.wideiv = trunc i64 %indvars.iv.next to i32
  %exitcond = icmp eq i32 %lftr.wideiv, %1
  br i1 %exitcond, label %._crit_edge, label %3

._crit_edge:                                      ; preds = %3
  store i64 %5, i64* inttoptr (i64 64 to i64*), align 64, !tbaa !5
  br label %6

; <label>:6                                       ; preds = %._crit_edge, %0
  ret void
}

attributes #0 = { nounwind optsize uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.5-1ubuntu1 (trunk) (based on LLVM 3.5)"}
!1 = metadata !{metadata !2, metadata !2, i64 0}
!2 = metadata !{metadata !"int", metadata !3, i64 0}
!3 = metadata !{metadata !"omnipotent char", metadata !4, i64 0}
!4 = metadata !{metadata !"Simple C/C++ TBAA"}
!5 = metadata !{metadata !6, metadata !6, i64 0}
!6 = metadata !{metadata !"long", metadata !3, i64 0}
