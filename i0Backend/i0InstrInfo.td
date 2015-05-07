def imm_i64 : Operand<i64>{
  let PrintMethod = "printImm64";
}
def imm_i32 : Operand<i32>{
  let PrintMethod = "printImm32";
}
def imm_i8 : Operand<i8>{
  let PrintMethod = "printImm8";
}
def mem_abs64 : Operand<i64>{
  let PrintMethod = "printMemAbs";
}

def SDT_i0_JmpLink : SDTypeProfile<0, 1, [SDTCisVT<0, iPTR>]>;
def SDT_i0_Ret : SDTypeProfile<0, 1, [SDTCisInt<0>]>;

def i0Ret : SDNode<"i0ISD::Ret", SDTNone,
  [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

def i0JmpLink : SDNode<"i0ISD::JmpLink", SDT_i0_JmpLink,
  [SDNPHasChain, SDNPOutGlue, SDNPOptInGlue, SDNPVariadic]>;

def SDT_i0_CallSeqStart : SDCallSeqStart<[SDTCisVT<0, i64>]>;
def SDT_i0_CallSeqEnd   : SDCallSeqEnd<[SDTCisVT<0, i64>, SDTCisVT<1, i64>]>;

def callseq_start : SDNode<"ISD::CALLSEQ_START", SDT_i0_CallSeqStart, [SDNPHasChain, SDNPOutGlue]>;
def callseq_end   : SDNode<"ISD::CALLSEQ_END", SDT_i0_CallSeqEnd, [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue]>;

let Defs=[SPq], Uses=[SPq] in {

def ADJCALLSTACKDOWN : i0Pseudo<(outs), (ins imm_i64:$amt),
  "!ADJCALLSTACKDOWN $amt", [(callseq_start timm:$amt)]>;
def ADJCALLSTACKUP : i0Pseudo<(outs), (ins imm_i64:$amt1, imm_i64:$amt2),
  "!ADJCALLSTACKUP $amt1", [(callseq_end timm:$amt1, timm:$amt2)]>;

}

//def simm32 : Operand

def mem : Operand<i64> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops GR64, imm_i32);
  let EncoderMethod = "getMemEncoding";
}

def brtarget : Operand<OtherVT>{

  let OperandType = "OPERAND_PCREL";
  let EncoderMethod = "getJumpTargetOpValue";
  let DecoderMethod = "DecodeJumpRelativeTarget";
}

def calltarget : Operand<iPTR>{
  let EncoderMethod = "getJumpTargetOpValue";
}

def imm_64 : ImmLeaf<i64, [{return true;}]>;
def imm_32 : ImmLeaf<i32, [{return true;}]>;
def imm_8 : ImmLeaf<i8, [{return true;}]>;
//def mem_abs : ImmLeaf<iPTR, [{return true;}]>;

class ArithLogicRRR64<bits<11> op, string asmstr, SDNode opnode>
: i0InsAri64rrr<op, (outs GR64:$ra), (ins GR64:$rb, GR64:$rc),
  !strconcat(asmstr, "\t$rb, $rc, $ra"), [(set GR64:$ra, (opnode GR64:$rb, GR64:$rc))], NoItinerary>{
}

class ArithLogicRIR64<bits<11> op, string asmstr, SDNode opnode>
: i0InsAri64rir<op, (outs GR64:$rout), (ins GR64:$rin, imm_i64:$imm64),
  !strconcat(asmstr, "\t$rin, $imm64, $rout"), [(set GR64:$rout, (opnode GR64:$rin, imm_64:$imm64))], NoItinerary>{
}

class ArithLogicIRR64<bits<11> op, string asmstr, SDNode opnode>
: i0InsAri64irr<op, (outs GR64:$rout), (ins imm_i64:$imm64, GR64:$rin),
  !strconcat(asmstr, "\t$imm64, $rin, $rout"), [(set GR64:$rout, (opnode imm_64:$imm64, GR64:$rin))], NoItinerary>{
}

class SetccRRR64<bits<11> op, string asmstr, PatFrag b_cond>
: i0InsAri64rrr<op, (outs GR64:$ra), (ins GR64:$rb, GR64:$rc),
  !strconcat(asmstr, "\t$rb, $rc, $ra"), [(set GR64:$ra, (i64 (b_cond GR64:$rb, GR64:$rc)))], NoItinerary>{
}

class SetccRIR64<bits<11> op, string asmstr, PatFrag b_cond>
: i0InsAri64rir<op, (outs GR64:$rout), (ins GR64:$rin, imm_i64:$imm64),
  !strconcat(asmstr, "\t$rin, $imm64, $rout"), [(set GR64:$rout, (i64 (b_cond GR64:$rin, imm_64:$imm64)))], NoItinerary>{
}

class SetccIRR64<bits<11> op, string asmstr, PatFrag b_cond>
: i0InsAri64irr<op, (outs GR64:$rout), (ins imm_i64:$imm64, GR64:$rin),
  !strconcat(asmstr, "\t$imm64, $rin, $rout"), [(set GR64:$rout, (i64 (b_cond imm_64:$imm64, GR64:$rin)))], NoItinerary>{
}

//def MOVir : i0InsMov64ir<(outs GR64:$reg), (ins imm_i64:$imm64), "mov \t$imm64, $reg", [(set GR64:$reg, imm_64:$imm64)], NoItinerary>;
def MOVrr : i0InsMov64rr<(outs GR64:$rout), (ins GR64:$rin), "mov \t$rin, $rout", [], NoItinerary>;

multiclass Setcc64<bits<11> op, string asmstr, PatFrag b_cond> {

def rrr : SetccRRR64<op, asmstr, b_cond>;
def rir : SetccRIR64<op, asmstr, b_cond>;
def irr : SetccIRR64<op, asmstr, b_cond>;

}

multiclass ArithLogic64<bits<11> op, string asmstr, SDNode opnode> {

def rrr : ArithLogicRRR64<op, asmstr, opnode>;
def rir : ArithLogicRIR64<op, asmstr, opnode>;
def irr : ArithLogicIRR64<op, asmstr, opnode>;
}

multiclass ArithLogic64Comm<bits<11> op, string asmstr, SDNode opnode> {

def rrr : ArithLogicRRR64<op, asmstr, opnode>;
def rir : ArithLogicRIR64<op, asmstr, opnode>;
//def irr : ArithLogicIRR64<op, asmstr, opnode>;
}

class BranchCC64RI<bits<4> bopt, string asmstr, PatFrag b_cond>
: i0InsBCCri64<bopt, (outs), (ins GR64:$reg, imm_i64:$imm64, brtarget:$jmptarget),
  !strconcat(asmstr, "\t$reg, $imm64, $jmptarget"), [(brcond (i64 (b_cond GR64:$reg, imm_64:$imm64)), bb:$jmptarget)], NoItinerary>{
}

class BranchCC64RR<bits<4> bopt, string asmstr, PatFrag b_cond>
: i0InsBCCrr64<bopt, (outs), (ins GR64:$reg1, GR64:$reg2, brtarget:$jmptarget),
  !strconcat(asmstr, "\t$reg1, $reg2, $jmptarget"), [(brcond (i64 (b_cond GR64:$reg1, GR64:$reg2)), bb:$jmptarget)], NoItinerary>{
}

class BranchCC64IR<bits<4> bopt, string asmstr, PatFrag b_cond>
: i0InsBCCir64<bopt, (outs), (ins imm_i64:$imm64, GR64:$reg, brtarget:$jmptarget),
  !strconcat(asmstr, "\t$imm64, $reg, $jmptarget"), [(brcond (i64 (b_cond imm_64:$imm64, GR64:$reg)), bb:$jmptarget)], NoItinerary>{
}

def JMP : i0InsJmp<(outs), (ins brtarget:$jmptarget), "jmp \t$jmptarget", [(br bb:$jmptarget)], NoItinerary>;
def JMPINDR : i0InsIndrBrR<(outs), (ins GR64:$reg), "jmpr \t$reg", [(brind GR64:$reg)], NoItinerary>{
  let isBranch = 1;
  let isIndirectBranch = 1;
}

def RetLR : i0InsIndrBrR<(outs), (ins), "ret", [(i0Ret)], NoItinerary>{
  let isReturn = 1;
  let hasCtrlDep = 1;
}

def RET : i0InsIndrBrR<(outs), (ins GR64:$reg), "retr \t$reg", [(brind GR64:$reg)], NoItinerary> {
  let isReturn = 1;
  let hasCtrlDep = 1;
  let hasExtraSrcRegAllocReq = 1;
}

multiclass BranchCC64<bits<4> bopt, string asmstr, PatFrag b_cond> {

def rr : BranchCC64RR<bopt, asmstr, b_cond>;
def ri : BranchCC64RI<bopt, asmstr, b_cond>;
def ir : BranchCC64IR<bopt, asmstr, b_cond>;

}

def addr : ComplexPattern<iPTR, 2, "SelectAddr", [frameindex], [SDNPWantParent]>;
def addrabs : ComplexPattern<iPTR, 1, "SelectAddrAbs", [imm], [SDNPWantParent]>;
class LoadRMDisp<Attr attr, string asmstr, bits<2> ext, PatFrag OpNode> :
  i0InsLoadR64Disp<attr, ext, (outs GR64:$rvalue), (ins mem:$addr), !strconcat(asmstr, " \t$rvalue, $addr"),
    [(set GR64:$rvalue, (OpNode addr:$addr))], NoItinerary> {
}

class LoadRMIndr<Attr attr, string asmstr, bits<2> ext, PatFrag OpNode> :
  i0InsLoadR64Indr<attr, ext, (outs GR64:$rvalue), (ins mem_abs64:$addr), !strconcat(asmstr, " \t$rvalue, $addr"),
    [(set GR64:$rvalue, (OpNode imm_64:$addr))], NoItinerary> {
}

class StoreRMDisp<Attr attr, string asmstr, PatFrag OpNode> :
  i0InsStoreR64<attr, (outs), (ins GR64:$rvalue, mem:$addr), !strconcat(asmstr, " \t$rvalue, $addr"),
    [(OpNode GR64:$rvalue, addr:$addr)], NoItinerary> {
}

class StoreRMIndr<Attr attr, string asmstr, PatFrag OpNode> :
  i0InsStoreR64<attr, (outs), (ins GR64:$rvalue, mem_abs64:$addr), !strconcat(asmstr, " \t$rvalue, $addr"),
    [(OpNode GR64:$rvalue, imm_64:$addr)], NoItinerary> {
}

def Storei64Disp :
  i0InsStoreI64<(outs), (ins imm_i64:$imm64, mem:$addr), "storei64 $imm64, $addr",
    [(store imm_64:$imm64, addr:$addr)], NoItinerary> ;

def Storei32Disp :
  i0InsStoreI32<(outs), (ins imm_i32:$imm32, mem:$addr), "storei32 $imm32, $addr",
    [(store imm_32:$imm32, addr:$addr)], NoItinerary> ;

def Storei8Disp :
  i0InsStoreI8<(outs), (ins imm_i8:$imm8, mem:$addr), "storei8 $imm8, $addr",
    [(store imm_8:$imm8, addr:$addr)], NoItinerary> ;

def Storei64Indr :
  i0InsStoreI64<(outs), (ins imm_i64:$imm64, mem_abs64:$addr), "storei64 $imm64, $addr",
    [(store imm_64:$imm64, imm_64:$addr)], NoItinerary> ;

def Storei32Indr :
  i0InsStoreI32<(outs), (ins imm_i32:$imm32, mem_abs64:$addr), "storei32 $imm32, $addr",
    [(store imm_32:$imm32, imm_64:$addr)], NoItinerary> ;

def Storei8Indr :
  i0InsStoreI8<(outs), (ins imm_i8:$imm8, mem_abs64:$addr), "storei8 $imm8, $addr",
    [(store imm_8:$imm8, imm_64:$addr)], NoItinerary> ;


multiclass LoadR64 {

  def _s8_disp : LoadRMDisp<AttrB, "loadrs8", 1, sextloadi8>;
  def _s32_disp : LoadRMDisp<AttrF, "loadrs32", 1, sextloadi32>;
  def _z8_disp : LoadRMDisp<AttrB, "loadrz8", 0, zextloadi8>;
  def _z32_disp : LoadRMDisp<AttrF, "loadrz32", 0, zextloadi32>;
  def _a8_disp : LoadRMDisp<AttrB, "loadra8", 2, extloadi8>;
  def _a32_disp : LoadRMDisp<AttrF, "loadra32", 2, extloadi32>;
  def _64_disp : LoadRMDisp<AttrE, "loadr64", 0, load>;

  def _s8_indr : LoadRMIndr<AttrB, "loadrs8", 1, sextloadi8>;
  def _s32_indr : LoadRMIndr<AttrF, "loadrs32", 1, sextloadi32>;
  def _z8_indr : LoadRMIndr<AttrB, "loadrz8", 0, zextloadi8>;
  def _z32_indr : LoadRMIndr<AttrF, "loadrz32", 0, zextloadi32>;
  def _a8_indr : LoadRMIndr<AttrB, "loadra8", 2, extloadi8>;
  def _a32_indr : LoadRMIndr<AttrF, "loadra32", 2, extloadi32>;
  def _64_indr : LoadRMIndr<AttrE, "loadr64", 0, load>;
}

multiclass StoreR64 {

  def _8_disp : StoreRMDisp<AttrB, "storer8", truncstorei8>;
  def _32_disp : StoreRMDisp<AttrF, "storer32", truncstorei32>;
  def _64_disp : StoreRMDisp<AttrE, "storer64", store>;

  def _8_indr : StoreRMIndr<AttrB, "storer8", truncstorei8>;
  def _32_indr : StoreRMIndr<AttrF, "storer32", truncstorei32>;
  def _64_indr : StoreRMIndr<AttrE, "storer64", store>;
}

defm Loadr : LoadR64;
defm Storer : StoreR64;

defm ADD : ArithLogic64Comm<0x03, "add ", add>;
defm SUB : ArithLogic64<0x06, "sub ", sub>;
defm MUL : ArithLogic64Comm<0x09, "mul ", mul>;
defm UDIV : ArithLogic64<0xf0, "udiv ", udiv>;
defm SDIV : ArithLogic64<0xf1, "sdiv ", sdiv>;
defm UREM : ArithLogic64<0xf2, "urem ", urem>;
defm SREM : ArithLogic64<0xf3, "srem ", srem>;
defm AND : ArithLogic64Comm<0x18, "and ", and>;
defm OR : ArithLogic64Comm<0x1b, "or ", or>;
defm XOR : ArithLogic64Comm<0x1e, "xor ", xor>;
defm SHL : ArithLogic64<0xf4, "shl ", shl>;
defm SRA : ArithLogic64<0xf5, "sra ", sra>;
defm SRL : ArithLogic64<0xf6, "srl ", srl>;

defm BLE : BranchCC64<0x00, "ble ", setle>;
defm BGE : BranchCC64<0x01, "bge ", setge>;
defm BEQ : BranchCC64<0x02, "beq ", seteq>;
defm BLT : BranchCC64<0x03, "blt ", setlt>;
defm BGT : BranchCC64<0x04, "bgt ", setgt>;
defm BNE : BranchCC64<0x05, "bne ", setne>;
defm BULE : BranchCC64<0x06, "bule ", setule>;
defm BUGE : BranchCC64<0x07, "buge ", setuge>;
defm BUEQ : BranchCC64<0x08, "bueq ", setueq>;
defm BULT : BranchCC64<0x09, "bult ", setult>;
defm BUGT : BranchCC64<0x0a, "bugt ", setugt>;
defm BUNE : BranchCC64<0x0b, "bune ", setune>;

defm SETLE : Setcc64<0xf7, "setle ", setle>;
defm SETEQ : Setcc64<0xf8, "seteq ", seteq>;
defm SETLT : Setcc64<0xf9, "setlt ", setlt>;
defm SETNE : Setcc64<0xfa, "setne ", setne>;
defm SETULE : Setcc64<0xfb, "setule ", setule>;
defm SETUEQ : Setcc64<0xfc, "setueq ", setueq>;
defm SETULT : Setcc64<0xfd, "setult ", setult>;
defm SETUNE : Setcc64<0xfe, "setune ", setune>;



//def addr : ComplexPattern<iPTR, 2
