; ModuleID = 'complex-O0.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define void @test() #0 {
entry:
  %i = alloca i64, align 8
  %j = alloca i64, align 8
  store i64 0, i64* %i, align 8
  %0 = load i64* inttoptr (i64 128 to i64*), align 8
  store i64 %0, i64* %j, align 8
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %1 = load i64* %i, align 8
  %2 = load i64* %j, align 8
  %cmp = icmp slt i64 %1, %2
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %3 = load i64* %i, align 8
  %4 = load i64* inttoptr (i64 64 to i64*), align 8
  %mul = mul nsw i64 %4, %3
  store i64 %mul, i64* inttoptr (i64 64 to i64*), align 8
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %5 = load i64* %i, align 8
  %inc = add nsw i64 %5, 1
  store i64 %inc, i64* %i, align 8
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret void
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.6.0 (/home/progman/workspace/llvm/llvm_3_6_0/llvm.Cpu0/tools/../../cfe-3.6.0.src 160fdc1e67559ec928111c6866f47fe455c403c5) (llvm/llvm_3_6_0/llvm-3.6.0.src 7525232014ee063b098b3674a4126db433092f52)"}
