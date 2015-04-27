; ModuleID = 'branch.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind readnone uwtable
define i32 @test(i32 %x) #0 {
  %1 = icmp slt i32 %x, 0
  br i1 %1, label %2, label %4

; <label>:2                                       ; preds = %0
  %3 = shl nsw i32 %x, 1
  br label %6

; <label>:4                                       ; preds = %0
  %5 = mul nsw i32 %x, 3
  br label %6

; <label>:6                                       ; preds = %4, %2
  %.0 = phi i32 [ %3, %2 ], [ %5, %4 ]
  ret i32 %.0
}

attributes #0 = { nounwind readnone uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.5-1ubuntu1 (trunk) (based on LLVM 3.5)"}
