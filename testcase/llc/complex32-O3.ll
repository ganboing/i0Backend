; ModuleID = 'complex32-O3.bc'
target datalayout = "E-m:m-p:32:32-i8:8:32-i16:16:32-i64:64-n32-S64"
target triple = "mips-unknown-linux-gnu"

; Function Attrs: nounwind
define void @test() #0 {
entry:
  %0 = load i32* inttoptr (i32 128 to i32*), align 128, !tbaa !1
  %cmp3 = icmp sgt i32 %0, 0
  br i1 %cmp3, label %for.body.lr.ph, label %for.end

for.body.lr.ph:                                   ; preds = %entry
  %.promoted = load i32* inttoptr (i32 64 to i32*), align 64, !tbaa !1
  %1 = add i32 %0, -1
  br label %for.body

for.body:                                         ; preds = %for.body, %for.body.lr.ph
  %mul5 = phi i32 [ %.promoted, %for.body.lr.ph ], [ %mul, %for.body ]
  %i.04 = phi i32 [ 0, %for.body.lr.ph ], [ %inc, %for.body ]
  %mul = mul nsw i32 %mul5, %i.04
  %inc = add nuw nsw i32 %i.04, 1
  %exitcond = icmp eq i32 %i.04, %1
  br i1 %exitcond, label %for.cond.for.end_crit_edge, label %for.body

for.cond.for.end_crit_edge:                       ; preds = %for.body
  %mul.lcssa = phi i32 [ %mul, %for.body ]
  store i32 %mul.lcssa, i32* inttoptr (i32 64 to i32*), align 64, !tbaa !1
  br label %for.end

for.end:                                          ; preds = %for.cond.for.end_crit_edge, %entry
  ret void
}

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.6.0 (/home/progman/workspace/llvm/llvm_3_6_0/llvm.Cpu0/tools/../../cfe-3.6.0.src 160fdc1e67559ec928111c6866f47fe455c403c5) (llvm/llvm_3_6_0/llvm-3.6.0.src 7525232014ee063b098b3674a4126db433092f52)"}
!1 = !{!2, !2, i64 0}
!2 = !{!"int", !3, i64 0}
!3 = !{!"omnipotent char", !4, i64 0}
!4 = !{!"Simple C/C++ TBAA"}
