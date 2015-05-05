; ModuleID = 'complex-Os.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind optsize uwtable
define void @test() #0 {
entry:
  %0 = load i64* inttoptr (i64 128 to i64*), align 128, !tbaa !1
  %cmp3 = icmp sgt i64 %0, 0
  br i1 %cmp3, label %for.body.lr.ph, label %for.end

for.body.lr.ph:                                   ; preds = %entry
  %.promoted = load i64* inttoptr (i64 64 to i64*), align 64, !tbaa !1
  %1 = add i64 %0, -1
  br label %for.body

for.body:                                         ; preds = %for.body, %for.body.lr.ph
  %mul5 = phi i64 [ %.promoted, %for.body.lr.ph ], [ %mul, %for.body ]
  %i.04 = phi i64 [ 0, %for.body.lr.ph ], [ %inc, %for.body ]
  %mul = mul nsw i64 %mul5, %i.04
  %inc = add nuw nsw i64 %i.04, 1
  %exitcond = icmp eq i64 %i.04, %1
  br i1 %exitcond, label %for.cond.for.end_crit_edge, label %for.body

for.cond.for.end_crit_edge:                       ; preds = %for.body
  store i64 %mul, i64* inttoptr (i64 64 to i64*), align 64, !tbaa !1
  br label %for.end

for.end:                                          ; preds = %for.cond.for.end_crit_edge, %entry
  ret void
}

attributes #0 = { nounwind optsize uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.6.0 (/home/progman/workspace/llvm/llvm_3_6_0/llvm.Cpu0/tools/../../cfe-3.6.0.src 160fdc1e67559ec928111c6866f47fe455c403c5) (llvm/llvm_3_6_0/llvm-3.6.0.src 7525232014ee063b098b3674a4126db433092f52)"}
!1 = !{!2, !2, i64 0}
!2 = !{!"long", !3, i64 0}
!3 = !{!"omnipotent char", !4, i64 0}
!4 = !{!"Simple C/C++ TBAA"}
