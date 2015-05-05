; ModuleID = 'complex-O3.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define void @test() #0 {
entry:
  %0 = load i64* inttoptr (i64 128 to i64*), align 128, !tbaa !1
  %cmp3 = icmp sgt i64 %0, 0
  br i1 %cmp3, label %for.body.lr.ph, label %for.end

for.body.lr.ph:                                   ; preds = %entry
  %.promoted = load i64* inttoptr (i64 64 to i64*), align 64, !tbaa !1
  %1 = add i64 %0, -1
  %backedge.overflow = icmp eq i64 %0, 0
  br i1 %backedge.overflow, label %for.body.preheader, label %overflow.checked

overflow.checked:                                 ; preds = %for.body.lr.ph
  %n.vec = and i64 %0, -2
  %cmp.zero = icmp eq i64 %n.vec, 0
  br i1 %cmp.zero, label %middle.block, label %vector.body.preheader

vector.body.preheader:                            ; preds = %overflow.checked
  br label %vector.body

vector.body:                                      ; preds = %vector.body, %vector.body.preheader
  %index = phi i64 [ %index.next, %vector.body ], [ 0, %vector.body.preheader ]
  %vec.phi = phi i64 [ %2, %vector.body ], [ %.promoted, %vector.body.preheader ]
  %vec.phi6 = phi i64 [ %3, %vector.body ], [ 1, %vector.body.preheader ]
  %induction79 = or i64 %index, 1
  %2 = mul nsw i64 %vec.phi, %index
  %3 = mul nsw i64 %vec.phi6, %induction79
  %index.next = add i64 %index, 2
  %4 = icmp eq i64 %index.next, %n.vec
  br i1 %4, label %middle.block.loopexit, label %vector.body, !llvm.loop !5

middle.block.loopexit:                            ; preds = %vector.body
  %.lcssa11 = phi i64 [ %3, %vector.body ]
  %.lcssa = phi i64 [ %2, %vector.body ]
  br label %middle.block

middle.block:                                     ; preds = %middle.block.loopexit, %overflow.checked
  %resume.val = phi i64 [ 0, %overflow.checked ], [ %n.vec, %middle.block.loopexit ]
  %rdx.vec.exit.phi = phi i64 [ %.promoted, %overflow.checked ], [ %.lcssa, %middle.block.loopexit ]
  %rdx.vec.exit.phi8 = phi i64 [ 1, %overflow.checked ], [ %.lcssa11, %middle.block.loopexit ]
  %bin.rdx = mul i64 %rdx.vec.exit.phi8, %rdx.vec.exit.phi
  %cmp.n = icmp eq i64 %0, %resume.val
  br i1 %cmp.n, label %for.cond.for.end_crit_edge, label %for.body.preheader

for.body.preheader:                               ; preds = %middle.block, %for.body.lr.ph
  %mul5.ph = phi i64 [ %.promoted, %for.body.lr.ph ], [ %bin.rdx, %middle.block ]
  %i.04.ph = phi i64 [ 0, %for.body.lr.ph ], [ %resume.val, %middle.block ]
  br label %for.body

for.body:                                         ; preds = %for.body, %for.body.preheader
  %mul5 = phi i64 [ %mul, %for.body ], [ %mul5.ph, %for.body.preheader ]
  %i.04 = phi i64 [ %inc, %for.body ], [ %i.04.ph, %for.body.preheader ]
  %mul = mul nsw i64 %mul5, %i.04
  %inc = add nuw nsw i64 %i.04, 1
  %exitcond = icmp eq i64 %i.04, %1
  br i1 %exitcond, label %for.cond.for.end_crit_edge.loopexit, label %for.body, !llvm.loop !8

for.cond.for.end_crit_edge.loopexit:              ; preds = %for.body
  %mul.lcssa10 = phi i64 [ %mul, %for.body ]
  br label %for.cond.for.end_crit_edge

for.cond.for.end_crit_edge:                       ; preds = %for.cond.for.end_crit_edge.loopexit, %middle.block
  %mul.lcssa = phi i64 [ %bin.rdx, %middle.block ], [ %mul.lcssa10, %for.cond.for.end_crit_edge.loopexit ]
  store i64 %mul.lcssa, i64* inttoptr (i64 64 to i64*), align 64, !tbaa !1
  br label %for.end

for.end:                                          ; preds = %for.cond.for.end_crit_edge, %entry
  ret void
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.6.0 (/home/progman/workspace/llvm/llvm_3_6_0/llvm.Cpu0/tools/../../cfe-3.6.0.src 160fdc1e67559ec928111c6866f47fe455c403c5) (llvm/llvm_3_6_0/llvm-3.6.0.src 7525232014ee063b098b3674a4126db433092f52)"}
!1 = !{!2, !2, i64 0}
!2 = !{!"long", !3, i64 0}
!3 = !{!"omnipotent char", !4, i64 0}
!4 = !{!"Simple C/C++ TBAA"}
!5 = distinct !{!5, !6, !7}
!6 = !{!"llvm.loop.vectorize.width", i32 1}
!7 = !{!"llvm.loop.interleave.count", i32 1}
!8 = distinct !{!8, !6, !7}
