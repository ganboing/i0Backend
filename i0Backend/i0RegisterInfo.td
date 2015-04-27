
class I0Reg<string n, bits<16> Enc, list<Register> subregs = []> : Register<n>{
  let Namespace = "i0";
  let HWEncoding = Enc;
  //let SubRegs = subregs;
}

let Namespace = "i0" in {
  def sub_16bit : SubRegIndex<16>;
  def sub_32bit : SubRegIndex<32>;
  def sub_64bit : SubRegIndex<64>;
}

class R8<string n, bits<16> Enc> : I0Reg<n, Enc>;
class R16<string n, bits<16> Enc, list<Register> subreg> : I0Reg<n, Enc, subreg>{
  //let SubRegIndices = [sub_16bit];
}
class R32<string n, bits<16> Enc, list<Register> subreg> : I0Reg<n, Enc, subreg>{
  //let SubRegIndices = [sub_32bit];
}
class R64<string n, bits<16> Enc, list<Register> subreg> : I0Reg<n, Enc, subreg>{
//TODO  
//let SubRegIndices = [sub_64bit];
}
/*
def R0b : R8<"r0b", 0>;
def R1b : R8<"r1b", 1>;
def R2b : R8<"r2b", 2>;
def R3b : R8<"r3b", 3>;
def R4b : R8<"r4b", 4>;
def R5b : R8<"r5b", 5>;
def SPb : R8<"spb", 6>;
def BPb : R8<"bpb", 7>;

def R0w : R16<"r0w", 0, R0b>;
def R1w : R16<"r1w", 1, R1b>;
def R2w : R16<"r2w", 2, R2b>;
def R3w : R16<"r3w", 3, R3b>;
def R4w : R16<"r4w", 4, R4b>;
def R5w : R16<"r5w", 5, R5b>;
def SPw : R16<"spw", 6, SPb>;
def BPw : R16<"bpw", 7, BPb>;

def R0l : R32<"r0l", 0, R0w>;
def R1l : R32<"r1l", 1, R1w>;
def R2l : R32<"r2l", 2, R2w>;
def R3l : R32<"r3l", 3, R3w>;
def R4l : R32<"r4l", 4, R4w>;
def R5l : R32<"r5l", 5, R5w>;
def SPl : R32<"spl", 6, SPw>;
def BPl : R32<"bpl", 7, BPw>;
*/
def R0q : R64<"r0q", 0, []>;//R0l>;
def R1q : R64<"r1q", 1, []>;//R1l>;
def R2q : R64<"r2q", 2, []>;//R2l>;
def R3q : R64<"r3q", 3, []>;//R3l>;
def R4q : R64<"r4q", 4, []>;//R4l>;
def LRq : R64<"lrq", 5, []>;//R5l>;
def SPq : R64<"spq", 6, []>;//SPl>;
def BPq : R64<"bpq", 7, []>;//BPl>;
/*
def GR8 : RegisterClass<"i0", [i8], 8, (add
 R0b, R1b, R2b, R3b, R4b, R5b, SPb, BPb)>;

def GR16 : RegisterClass<"i0", [i16], 16, (add
 R0w, R1w, R2w, R3w, R4w, R5w, SPw, BPw)>;

def GR32 : RegisterClass<"i0", [i32], 32, (add
 R0l, R1l, R2l, R3l, R4l, R5l, SPl, BPl)>;
*/
def GR64 : RegisterClass<"i0", [i64], 64, (add
 R0q, R1q, R2q, R3q, R4q, LRq, SPq, BPq)>;

