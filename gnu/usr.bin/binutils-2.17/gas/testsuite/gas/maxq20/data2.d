#objdump: -dw
#name: 2nd Move operations

.*: +file format .*

Disassembly of section .text:
0+000 <foo>:
   0:	01 48 [ 	]*MOVE  PSF, #01h
   2:	08 c8 [ 	]*MOVE  PSF, AP
   4:	18 c8 [ 	]*MOVE  PSF, APC
   6:	58 c8 [ 	]*MOVE  PSF, IC
   8:	68 c8 [ 	]*MOVE  PSF, IMR
   a:	88 c8 [ 	]*MOVE  PSF, SC
   c:	b8 c8 [ 	]*MOVE  PSF, IIR
   e:	e8 c8 [ 	]*MOVE  PSF, CKCN
  10:	f8 c8 [ 	]*MOVE  PSF, WDCN
  12:	09 c8 [ 	]*MOVE  PSF, A\[0\]
  14:	f9 c8 [ 	]*MOVE  PSF, A\[15\]
  16:	0a c8 [ 	]*MOVE  PSF, ACC
  18:	1a c8 [ 	]*MOVE  PSF, A\[AP\]
  1a:	0c c8 [ 	]*MOVE  PSF, IP
  1c:	0d c8 [ 	]*MOVE  PSF, @SP\-\-
  1e:	1d c8 [ 	]*MOVE  PSF, SP
  20:	2d c8 [ 	]*MOVE  PSF, IV
  22:	6d c8 [ 	]*MOVE  PSF, LC\[0\]
  24:	7d c8 [ 	]*MOVE  PSF, LC\[1\]
  26:	1e c8 [ 	]*MOVE  PSF, @BP\[OFFS\+\+\]
  28:	2e c8 [ 	]*MOVE  PSF, @BP\[OFFS\-\-\]
  2a:	3e c8 [ 	]*MOVE  PSF, OFFS
  2c:	4e c8 [ 	]*MOVE  PSF, DPC
  2e:	5e c8 [ 	]*MOVE  PSF, GR
  30:	6e c8 [ 	]*MOVE  PSF, GRL
  32:	7e c8 [ 	]*MOVE  PSF, BP
  34:	8e c8 [ 	]*MOVE  PSF, GRS
  36:	9e c8 [ 	]*MOVE  PSF, GRH
  38:	ae c8 [ 	]*MOVE  PSF, GRXL
  3a:	be c8 [ 	]*MOVE  PSF, FP
  3c:	0f c8 [ 	]*MOVE  PSF, @DP\[0\]
  3e:	4f c8 [ 	]*MOVE  PSF, @DP\[1\]
  40:	1f c8 [ 	]*MOVE  PSF, @DP\[0\]\+\+
  42:	5f c8 [ 	]*MOVE  PSF, @DP\[1\]\+\+
  44:	2f c8 [ 	]*MOVE  PSF, @DP\[0\]\-\-
  46:	6f c8 [ 	]*MOVE  PSF, @DP\[1\]\-\-
  48:	01 58 [ 	]*MOVE  IC, #01h
  4a:	08 d8 [ 	]*MOVE  IC, AP
  4c:	18 d8 [ 	]*MOVE  IC, APC
  4e:	48 d8 [ 	]*MOVE  IC, PSF
  50:	68 d8 [ 	]*MOVE  IC, IMR
  52:	88 d8 [ 	]*MOVE  IC, SC
  54:	b8 d8 [ 	]*MOVE  IC, IIR
  56:	e8 d8 [ 	]*MOVE  IC, CKCN
  58:	f8 d8 [ 	]*MOVE  IC, WDCN
  5a:	09 d8 [ 	]*MOVE  IC, A\[0\]
  5c:	f9 d8 [ 	]*MOVE  IC, A\[15\]
  5e:	0a d8 [ 	]*MOVE  IC, ACC
  60:	1a d8 [ 	]*MOVE  IC, A\[AP\]
  62:	0c d8 [ 	]*MOVE  IC, IP
  64:	0d d8 [ 	]*MOVE  IC, @SP\-\-
  66:	1d d8 [ 	]*MOVE  IC, SP
  68:	2d d8 [ 	]*MOVE  IC, IV
  6a:	6d d8 [ 	]*MOVE  IC, LC\[0\]
  6c:	7d d8 [ 	]*MOVE  IC, LC\[1\]
  6e:	1e d8 [ 	]*MOVE  IC, @BP\[OFFS\+\+\]
  70:	2e d8 [ 	]*MOVE  IC, @BP\[OFFS\-\-\]
  72:	3e d8 [ 	]*MOVE  IC, OFFS
  74:	4e d8 [ 	]*MOVE  IC, DPC
  76:	5e d8 [ 	]*MOVE  IC, GR
  78:	6e d8 [ 	]*MOVE  IC, GRL
  7a:	7e d8 [ 	]*MOVE  IC, BP
  7c:	8e d8 [ 	]*MOVE  IC, GRS
  7e:	9e d8 [ 	]*MOVE  IC, GRH
  80:	ae d8 [ 	]*MOVE  IC, GRXL
  82:	be d8 [ 	]*MOVE  IC, FP
  84:	0f d8 [ 	]*MOVE  IC, @DP\[0\]
  86:	4f d8 [ 	]*MOVE  IC, @DP\[1\]
  88:	1f d8 [ 	]*MOVE  IC, @DP\[0\]\+\+
  8a:	5f d8 [ 	]*MOVE  IC, @DP\[1\]\+\+
  8c:	2f d8 [ 	]*MOVE  IC, @DP\[0\]\-\-
  8e:	6f d8 [ 	]*MOVE  IC, @DP\[1\]\-\-
  90:	01 68 [ 	]*MOVE  IMR, #01h
  92:	08 e8 [ 	]*MOVE  IMR, AP
  94:	18 e8 [ 	]*MOVE  IMR, APC
  96:	48 e8 [ 	]*MOVE  IMR, PSF
  98:	58 e8 [ 	]*MOVE  IMR, IC
  9a:	88 e8 [ 	]*MOVE  IMR, SC
  9c:	b8 e8 [ 	]*MOVE  IMR, IIR
  9e:	e8 e8 [ 	]*MOVE  IMR, CKCN
  a0:	f8 e8 [ 	]*MOVE  IMR, WDCN
  a2:	09 e8 [ 	]*MOVE  IMR, A\[0\]
  a4:	f9 e8 [ 	]*MOVE  IMR, A\[15\]
  a6:	0a e8 [ 	]*MOVE  IMR, ACC
  a8:	1a e8 [ 	]*MOVE  IMR, A\[AP\]
  aa:	0c e8 [ 	]*MOVE  IMR, IP
  ac:	0d e8 [ 	]*MOVE  IMR, @SP\-\-
  ae:	1d e8 [ 	]*MOVE  IMR, SP
  b0:	2d e8 [ 	]*MOVE  IMR, IV
  b2:	6d e8 [ 	]*MOVE  IMR, LC\[0\]
  b4:	7d e8 [ 	]*MOVE  IMR, LC\[1\]
  b6:	1e e8 [ 	]*MOVE  IMR, @BP\[OFFS\+\+\]
  b8:	2e e8 [ 	]*MOVE  IMR, @BP\[OFFS\-\-\]
  ba:	3e e8 [ 	]*MOVE  IMR, OFFS
  bc:	4e e8 [ 	]*MOVE  IMR, DPC
  be:	5e e8 [ 	]*MOVE  IMR, GR
  c0:	6e e8 [ 	]*MOVE  IMR, GRL
  c2:	7e e8 [ 	]*MOVE  IMR, BP
  c4:	8e e8 [ 	]*MOVE  IMR, GRS
  c6:	9e e8 [ 	]*MOVE  IMR, GRH
  c8:	ae e8 [ 	]*MOVE  IMR, GRXL
  ca:	be e8 [ 	]*MOVE  IMR, FP
  cc:	0f e8 [ 	]*MOVE  IMR, @DP\[0\]
  ce:	4f e8 [ 	]*MOVE  IMR, @DP\[1\]
  d0:	1f e8 [ 	]*MOVE  IMR, @DP\[0\]\+\+
  d2:	5f e8 [ 	]*MOVE  IMR, @DP\[1\]\+\+
  d4:	2f e8 [ 	]*MOVE  IMR, @DP\[0\]\-\-
  d6:	6f e8 [ 	]*MOVE  IMR, @DP\[1\]\-\-
  d8:	01 09 [ 	]*MOVE  A\[0\], #01h
  da:	08 89 [ 	]*MOVE  A\[0\], AP
  dc:	18 89 [ 	]*MOVE  A\[0\], APC
  de:	48 89 [ 	]*MOVE  A\[0\], PSF
  e0:	58 89 [ 	]*MOVE  A\[0\], IC
  e2:	68 89 [ 	]*MOVE  A\[0\], IMR
  e4:	88 89 [ 	]*MOVE  A\[0\], SC
  e6:	b8 89 [ 	]*MOVE  A\[0\], IIR
  e8:	e8 89 [ 	]*MOVE  A\[0\], CKCN
  ea:	f8 89 [ 	]*MOVE  A\[0\], WDCN
  ec:	0a 89 [ 	]*MOVE  A\[0\], ACC
  ee:	1a 89 [ 	]*MOVE  A\[0\], A\[AP\]
  f0:	0c 89 [ 	]*MOVE  A\[0\], IP
  f2:	0d 89 [ 	]*MOVE  A\[0\], @SP\-\-
  f4:	1d 89 [ 	]*MOVE  A\[0\], SP
  f6:	2d 89 [ 	]*MOVE  A\[0\], IV
  f8:	6d 89 [ 	]*MOVE  A\[0\], LC\[0\]
  fa:	7d 89 [ 	]*MOVE  A\[0\], LC\[1\]
  fc:	1e 89 [ 	]*MOVE  A\[0\], @BP\[OFFS\+\+\]
  fe:	2e 89 [ 	]*MOVE  A\[0\], @BP\[OFFS\-\-\]
 100:	3e 89 [ 	]*MOVE  A\[0\], OFFS
 102:	4e 89 [ 	]*MOVE  A\[0\], DPC
 104:	5e 89 [ 	]*MOVE  A\[0\], GR
 106:	6e 89 [ 	]*MOVE  A\[0\], GRL
 108:	7e 89 [ 	]*MOVE  A\[0\], BP
 10a:	8e 89 [ 	]*MOVE  A\[0\], GRS
 10c:	9e 89 [ 	]*MOVE  A\[0\], GRH
 10e:	ae 89 [ 	]*MOVE  A\[0\], GRXL
 110:	be 89 [ 	]*MOVE  A\[0\], FP
 112:	0f 89 [ 	]*MOVE  A\[0\], @DP\[0\]
 114:	4f 89 [ 	]*MOVE  A\[0\], @DP\[1\]
 116:	1f 89 [ 	]*MOVE  A\[0\], @DP\[0\]\+\+
 118:	5f 89 [ 	]*MOVE  A\[0\], @DP\[1\]\+\+
 11a:	2f 89 [ 	]*MOVE  A\[0\], @DP\[0\]\-\-
 11c:	6f 89 [ 	]*MOVE  A\[0\], @DP\[1\]\-\-
 11e:	01 0a [ 	]*MOVE  ACC, #01h
 120:	08 8a [ 	]*MOVE  ACC, AP
 122:	18 8a [ 	]*MOVE  ACC, APC
 124:	48 8a [ 	]*MOVE  ACC, PSF
 126:	58 8a [ 	]*MOVE  ACC, IC
 128:	68 8a [ 	]*MOVE  ACC, IMR
 12a:	88 8a [ 	]*MOVE  ACC, SC
 12c:	b8 8a [ 	]*MOVE  ACC, IIR
 12e:	e8 8a [ 	]*MOVE  ACC, CKCN
 130:	f8 8a [ 	]*MOVE  ACC, WDCN
 132:	09 8a [ 	]*MOVE  ACC, A\[0\]
 134:	f9 8a [ 	]*MOVE  ACC, A\[15\]
 136:	0c 8a [ 	]*MOVE  ACC, IP
 138:	0d 8a [ 	]*MOVE  ACC, @SP\-\-
 13a:	1d 8a [ 	]*MOVE  ACC, SP
 13c:	2d 8a [ 	]*MOVE  ACC, IV
 13e:	6d 8a [ 	]*MOVE  ACC, LC\[0\]
 140:	7d 8a [ 	]*MOVE  ACC, LC\[1\]
 142:	1e 8a [ 	]*MOVE  ACC, @BP\[OFFS\+\+\]
 144:	2e 8a [ 	]*MOVE  ACC, @BP\[OFFS\-\-\]
 146:	3e 8a [ 	]*MOVE  ACC, OFFS
 148:	4e 8a [ 	]*MOVE  ACC, DPC
 14a:	5e 8a [ 	]*MOVE  ACC, GR
 14c:	6e 8a [ 	]*MOVE  ACC, GRL
 14e:	7e 8a [ 	]*MOVE  ACC, BP
 150:	8e 8a [ 	]*MOVE  ACC, GRS
 152:	9e 8a [ 	]*MOVE  ACC, GRH
 154:	ae 8a [ 	]*MOVE  ACC, GRXL
 156:	be 8a [ 	]*MOVE  ACC, FP
 158:	0f 8a [ 	]*MOVE  ACC, @DP\[0\]
 15a:	4f 8a [ 	]*MOVE  ACC, @DP\[1\]
 15c:	1f 8a [ 	]*MOVE  ACC, @DP\[0\]\+\+
 15e:	5f 8a [ 	]*MOVE  ACC, @DP\[1\]\+\+
 160:	2f 8a [ 	]*MOVE  ACC, @DP\[0\]\-\-
 162:	6f 8a [ 	]*MOVE  ACC, @DP\[1\]\-\-
 164:	01 0d [ 	]*MOVE  @\+\+SP, #01h
 166:	08 8d [ 	]*MOVE  @\+\+SP, AP
 168:	18 8d [ 	]*MOVE  @\+\+SP, APC
 16a:	48 8d [ 	]*MOVE  @\+\+SP, PSF
 16c:	58 8d [ 	]*MOVE  @\+\+SP, IC
 16e:	68 8d [ 	]*MOVE  @\+\+SP, IMR
 170:	88 8d [ 	]*MOVE  @\+\+SP, SC
 172:	b8 8d [ 	]*MOVE  @\+\+SP, IIR
 174:	e8 8d [ 	]*MOVE  @\+\+SP, CKCN
 176:	f8 8d [ 	]*MOVE  @\+\+SP, WDCN
 178:	09 8d [ 	]*MOVE  @\+\+SP, A\[0\]
 17a:	f9 8d [ 	]*MOVE  @\+\+SP, A\[15\]
 17c:	0a 8d [ 	]*MOVE  @\+\+SP, ACC
 17e:	1a 8d [ 	]*MOVE  @\+\+SP, A\[AP\]
 180:	0c 8d [ 	]*MOVE  @\+\+SP, IP
 182:	1d 8d [ 	]*MOVE  @\+\+SP, SP
 184:	2d 8d [ 	]*MOVE  @\+\+SP, IV
 186:	6d 8d [ 	]*MOVE  @\+\+SP, LC\[0\]
 188:	7d 8d [ 	]*MOVE  @\+\+SP, LC\[1\]
 18a:	1e 8d [ 	]*MOVE  @\+\+SP, @BP\[OFFS\+\+\]
 18c:	2e 8d [ 	]*MOVE  @\+\+SP, @BP\[OFFS\-\-\]
 18e:	3e 8d [ 	]*MOVE  @\+\+SP, OFFS
 190:	4e 8d [ 	]*MOVE  @\+\+SP, DPC
 192:	5e 8d [ 	]*MOVE  @\+\+SP, GR
 194:	6e 8d [ 	]*MOVE  @\+\+SP, GRL
 196:	7e 8d [ 	]*MOVE  @\+\+SP, BP
 198:	8e 8d [ 	]*MOVE  @\+\+SP, GRS
 19a:	9e 8d [ 	]*MOVE  @\+\+SP, GRH
 19c:	ae 8d [ 	]*MOVE  @\+\+SP, GRXL
 19e:	be 8d [ 	]*MOVE  @\+\+SP, FP
 1a0:	0f 8d [ 	]*MOVE  @\+\+SP, @DP\[0\]
 1a2:	4f 8d [ 	]*MOVE  @\+\+SP, @DP\[1\]
 1a4:	1f 8d [ 	]*MOVE  @\+\+SP, @DP\[0\]\+\+
 1a6:	5f 8d [ 	]*MOVE  @\+\+SP, @DP\[1\]\+\+
 1a8:	2f 8d [ 	]*MOVE  @\+\+SP, @DP\[0\]\-\-
 1aa:	6f 8d [ 	]*MOVE  @\+\+SP, @DP\[1\]\-\-
 1ac:	01 1d [ 	]*MOVE  SP, #01h
 1ae:	08 9d [ 	]*MOVE  SP, AP
 1b0:	18 9d [ 	]*MOVE  SP, APC
 1b2:	48 9d [ 	]*MOVE  SP, PSF
 1b4:	58 9d [ 	]*MOVE  SP, IC
 1b6:	68 9d [ 	]*MOVE  SP, IMR
 1b8:	88 9d [ 	]*MOVE  SP, SC
 1ba:	b8 9d [ 	]*MOVE  SP, IIR
 1bc:	e8 9d [ 	]*MOVE  SP, CKCN
 1be:	f8 9d [ 	]*MOVE  SP, WDCN
 1c0:	09 9d [ 	]*MOVE  SP, A\[0\]
 1c2:	f9 9d [ 	]*MOVE  SP, A\[15\]
 1c4:	0a 9d [ 	]*MOVE  SP, ACC
 1c6:	1a 9d [ 	]*MOVE  SP, A\[AP\]
 1c8:	0c 9d [ 	]*MOVE  SP, IP
 1ca:	2d 9d [ 	]*MOVE  SP, IV
 1cc:	6d 9d [ 	]*MOVE  SP, LC\[0\]
 1ce:	7d 9d [ 	]*MOVE  SP, LC\[1\]
 1d0:	1e 9d [ 	]*MOVE  SP, @BP\[OFFS\+\+\]
 1d2:	2e 9d [ 	]*MOVE  SP, @BP\[OFFS\-\-\]
 1d4:	3e 9d [ 	]*MOVE  SP, OFFS
 1d6:	4e 9d [ 	]*MOVE  SP, DPC
 1d8:	5e 9d [ 	]*MOVE  SP, GR
 1da:	6e 9d [ 	]*MOVE  SP, GRL
 1dc:	7e 9d [ 	]*MOVE  SP, BP
 1de:	8e 9d [ 	]*MOVE  SP, GRS
 1e0:	9e 9d [ 	]*MOVE  SP, GRH
 1e2:	ae 9d [ 	]*MOVE  SP, GRXL
 1e4:	be 9d [ 	]*MOVE  SP, FP
 1e6:	0f 9d [ 	]*MOVE  SP, @DP\[0\]
 1e8:	4f 9d [ 	]*MOVE  SP, @DP\[1\]
 1ea:	1f 9d [ 	]*MOVE  SP, @DP\[0\]\+\+
 1ec:	5f 9d [ 	]*MOVE  SP, @DP\[1\]\+\+
 1ee:	2f 9d [ 	]*MOVE  SP, @DP\[0\]\-\-
 1f0:	6f 9d [ 	]*MOVE  SP, @DP\[1\]\-\-
 1f2:	01 2d [ 	]*MOVE  IV, #01h
 1f4:	08 ad [ 	]*MOVE  IV, AP
 1f6:	18 ad [ 	]*MOVE  IV, APC
 1f8:	48 ad [ 	]*MOVE  IV, PSF
 1fa:	58 ad [ 	]*MOVE  IV, IC
 1fc:	68 ad [ 	]*MOVE  IV, IMR
 1fe:	88 ad [ 	]*MOVE  IV, SC
 200:	b8 ad [ 	]*MOVE  IV, IIR
 202:	e8 ad [ 	]*MOVE  IV, CKCN
 204:	f8 ad [ 	]*MOVE  IV, WDCN
 206:	09 ad [ 	]*MOVE  IV, A\[0\]
 208:	f9 ad [ 	]*MOVE  IV, A\[15\]
 20a:	0a ad [ 	]*MOVE  IV, ACC
 20c:	1a ad [ 	]*MOVE  IV, A\[AP\]
 20e:	0c ad [ 	]*MOVE  IV, IP
 210:	0d ad [ 	]*MOVE  IV, @SP\-\-
 212:	1d ad [ 	]*MOVE  IV, SP
 214:	2d ad [ 	]*MOVE  IV, IV
 216:	6d ad [ 	]*MOVE  IV, LC\[0\]
 218:	7d ad [ 	]*MOVE  IV, LC\[1\]
 21a:	1e ad [ 	]*MOVE  IV, @BP\[OFFS\+\+\]
 21c:	2e ad [ 	]*MOVE  IV, @BP\[OFFS\-\-\]
 21e:	3e ad [ 	]*MOVE  IV, OFFS
 220:	4e ad [ 	]*MOVE  IV, DPC
 222:	5e ad [ 	]*MOVE  IV, GR
 224:	6e ad [ 	]*MOVE  IV, GRL
 226:	7e ad [ 	]*MOVE  IV, BP
 228:	8e ad [ 	]*MOVE  IV, GRS
 22a:	9e ad [ 	]*MOVE  IV, GRH
 22c:	ae ad [ 	]*MOVE  IV, GRXL
 22e:	be ad [ 	]*MOVE  IV, FP
 230:	0f ad [ 	]*MOVE  IV, @DP\[0\]
 232:	4f ad [ 	]*MOVE  IV, @DP\[1\]
 234:	1f ad [ 	]*MOVE  IV, @DP\[0\]\+\+
 236:	5f ad [ 	]*MOVE  IV, @DP\[1\]\+\+
 238:	2f ad [ 	]*MOVE  IV, @DP\[0\]\-\-
 23a:	6f ad [ 	]*MOVE  IV, @DP\[1\]\-\-
 23c:	01 6d [ 	]*MOVE  LC\[0\], #01h
 23e:	08 ed [ 	]*MOVE  LC\[0\], AP
 240:	18 ed [ 	]*MOVE  LC\[0\], APC
 242:	48 ed [ 	]*MOVE  LC\[0\], PSF
 244:	58 ed [ 	]*MOVE  LC\[0\], IC
 246:	68 ed [ 	]*MOVE  LC\[0\], IMR
 248:	88 ed [ 	]*MOVE  LC\[0\], SC
 24a:	b8 ed [ 	]*MOVE  LC\[0\], IIR
 24c:	e8 ed [ 	]*MOVE  LC\[0\], CKCN
 24e:	f8 ed [ 	]*MOVE  LC\[0\], WDCN
 250:	09 ed [ 	]*MOVE  LC\[0\], A\[0\]
 252:	f9 ed [ 	]*MOVE  LC\[0\], A\[15\]
 254:	0a ed [ 	]*MOVE  LC\[0\], ACC
 256:	1a ed [ 	]*MOVE  LC\[0\], A\[AP\]
 258:	0c ed [ 	]*MOVE  LC\[0\], IP
 25a:	0d ed [ 	]*MOVE  LC\[0\], @SP\-\-
 25c:	1d ed [ 	]*MOVE  LC\[0\], SP
 25e:	2d ed [ 	]*MOVE  LC\[0\], IV
 260:	1e ed [ 	]*MOVE  LC\[0\], @BP\[OFFS\+\+\]
 262:	2e ed [ 	]*MOVE  LC\[0\], @BP\[OFFS\-\-\]
 264:	3e ed [ 	]*MOVE  LC\[0\], OFFS
 266:	4e ed [ 	]*MOVE  LC\[0\], DPC
 268:	5e ed [ 	]*MOVE  LC\[0\], GR
 26a:	6e ed [ 	]*MOVE  LC\[0\], GRL
 26c:	7e ed [ 	]*MOVE  LC\[0\], BP
 26e:	8e ed [ 	]*MOVE  LC\[0\], GRS
 270:	9e ed [ 	]*MOVE  LC\[0\], GRH
 272:	ae ed [ 	]*MOVE  LC\[0\], GRXL
 274:	be ed [ 	]*MOVE  LC\[0\], FP
 276:	0f ed [ 	]*MOVE  LC\[0\], @DP\[0\]
 278:	4f ed [ 	]*MOVE  LC\[0\], @DP\[1\]
 27a:	1f ed [ 	]*MOVE  LC\[0\], @DP\[0\]\+\+
 27c:	5f ed [ 	]*MOVE  LC\[0\], @DP\[1\]\+\+
 27e:	2f ed [ 	]*MOVE  LC\[0\], @DP\[0\]\-\-
 280:	6f ed [ 	]*MOVE  LC\[0\], @DP\[1\]\-\-
 282:	01 0e [ 	]*MOVE  @BP\[OFFS\], #01h
 284:	08 8e [ 	]*MOVE  @BP\[OFFS\], AP
 286:	18 8e [ 	]*MOVE  @BP\[OFFS\], APC
 288:	48 8e [ 	]*MOVE  @BP\[OFFS\], PSF
 28a:	58 8e [ 	]*MOVE  @BP\[OFFS\], IC
 28c:	68 8e [ 	]*MOVE  @BP\[OFFS\], IMR
 28e:	88 8e [ 	]*MOVE  @BP\[OFFS\], SC
 290:	b8 8e [ 	]*MOVE  @BP\[OFFS\], IIR
 292:	e8 8e [ 	]*MOVE  @BP\[OFFS\], CKCN
 294:	f8 8e [ 	]*MOVE  @BP\[OFFS\], WDCN
 296:	09 8e [ 	]*MOVE  @BP\[OFFS\], A\[0\]
 298:	f9 8e [ 	]*MOVE  @BP\[OFFS\], A\[15\]
 29a:	0a 8e [ 	]*MOVE  @BP\[OFFS\], ACC
 29c:	1a 8e [ 	]*MOVE  @BP\[OFFS\], A\[AP\]
 29e:	0c 8e [ 	]*MOVE  @BP\[OFFS\], IP
 2a0:	0d 8e [ 	]*MOVE  @BP\[OFFS\], @SP\-\-
 2a2:	1d 8e [ 	]*MOVE  @BP\[OFFS\], SP
 2a4:	2d 8e [ 	]*MOVE  @BP\[OFFS\], IV
 2a6:	6d 8e [ 	]*MOVE  @BP\[OFFS\], LC\[0\]
 2a8:	7d 8e [ 	]*MOVE  @BP\[OFFS\], LC\[1\]
 2aa:	3e 8e [ 	]*MOVE  @BP\[OFFS\], OFFS
 2ac:	4e 8e [ 	]*MOVE  @BP\[OFFS\], DPC
 2ae:	5e 8e [ 	]*MOVE  @BP\[OFFS\], GR
 2b0:	6e 8e [ 	]*MOVE  @BP\[OFFS\], GRL
 2b2:	7e 8e [ 	]*MOVE  @BP\[OFFS\], BP
 2b4:	8e 8e [ 	]*MOVE  @BP\[OFFS\], GRS
 2b6:	9e 8e [ 	]*MOVE  @BP\[OFFS\], GRH
 2b8:	ae 8e [ 	]*MOVE  @BP\[OFFS\], GRXL
 2ba:	be 8e [ 	]*MOVE  @BP\[OFFS\], FP
 2bc:	0f 8e [ 	]*MOVE  @BP\[OFFS\], @DP\[0\]
 2be:	4f 8e [ 	]*MOVE  @BP\[OFFS\], @DP\[1\]
 2c0:	1f 8e [ 	]*MOVE  @BP\[OFFS\], @DP\[0\]\+\+
 2c2:	5f 8e [ 	]*MOVE  @BP\[OFFS\], @DP\[1\]\+\+
 2c4:	2f 8e [ 	]*MOVE  @BP\[OFFS\], @DP\[0\]\-\-
 2c6:	6f 8e [ 	]*MOVE  @BP\[OFFS\], @DP\[1\]\-\-
 2c8:	01 1e [ 	]*MOVE  @BP\[\+\+OFFS\], #01h
 2ca:	08 9e [ 	]*MOVE  @BP\[\+\+OFFS\], AP
 2cc:	18 9e [ 	]*MOVE  @BP\[\+\+OFFS\], APC
 2ce:	48 9e [ 	]*MOVE  @BP\[\+\+OFFS\], PSF
 2d0:	58 9e [ 	]*MOVE  @BP\[\+\+OFFS\], IC
 2d2:	68 9e [ 	]*MOVE  @BP\[\+\+OFFS\], IMR
 2d4:	88 9e [ 	]*MOVE  @BP\[\+\+OFFS\], SC
 2d6:	b8 9e [ 	]*MOVE  @BP\[\+\+OFFS\], IIR
 2d8:	e8 9e [ 	]*MOVE  @BP\[\+\+OFFS\], CKCN
 2da:	f8 9e [ 	]*MOVE  @BP\[\+\+OFFS\], WDCN
 2dc:	09 9e [ 	]*MOVE  @BP\[\+\+OFFS\], A\[0\]
 2de:	f9 9e [ 	]*MOVE  @BP\[\+\+OFFS\], A\[15\]
 2e0:	0a 9e [ 	]*MOVE  @BP\[\+\+OFFS\], ACC
 2e2:	1a 9e [ 	]*MOVE  @BP\[\+\+OFFS\], A\[AP\]
 2e4:	0c 9e [ 	]*MOVE  @BP\[\+\+OFFS\], IP
 2e6:	1d 9e [ 	]*MOVE  @BP\[\+\+OFFS\], SP
 2e8:	2d 9e [ 	]*MOVE  @BP\[\+\+OFFS\], IV
 2ea:	6d 9e [ 	]*MOVE  @BP\[\+\+OFFS\], LC\[0\]
 2ec:	7d 9e [ 	]*MOVE  @BP\[\+\+OFFS\], LC\[1\]
 2ee:	3e 9e [ 	]*MOVE  @BP\[\+\+OFFS\], OFFS
 2f0:	4e 9e [ 	]*MOVE  @BP\[\+\+OFFS\], DPC
 2f2:	5e 9e [ 	]*MOVE  @BP\[\+\+OFFS\], GR
 2f4:	6e 9e [ 	]*MOVE  @BP\[\+\+OFFS\], GRL
 2f6:	7e 9e [ 	]*MOVE  @BP\[\+\+OFFS\], BP
 2f8:	8e 9e [ 	]*MOVE  @BP\[\+\+OFFS\], GRS
 2fa:	9e 9e [ 	]*MOVE  @BP\[\+\+OFFS\], GRH
 2fc:	ae 9e [ 	]*MOVE  @BP\[\+\+OFFS\], GRXL
 2fe:	be 9e [ 	]*MOVE  @BP\[\+\+OFFS\], FP
 300:	0f 9e [ 	]*MOVE  @BP\[\+\+OFFS\], @DP\[0\]
 302:	4f 9e [ 	]*MOVE  @BP\[\+\+OFFS\], @DP\[1\]
 304:	2f 9e [ 	]*MOVE  @BP\[\+\+OFFS\], @DP\[0\]\-\-
 306:	6f 9e [ 	]*MOVE  @BP\[\+\+OFFS\], @DP\[1\]\-\-
 308:	01 2e [ 	]*MOVE  @BP\[\-\-OFFS\], #01h
 30a:	08 ae [ 	]*MOVE  @BP\[\-\-OFFS\], AP
 30c:	18 ae [ 	]*MOVE  @BP\[\-\-OFFS\], APC
 30e:	48 ae [ 	]*MOVE  @BP\[\-\-OFFS\], PSF
 310:	58 ae [ 	]*MOVE  @BP\[\-\-OFFS\], IC
 312:	68 ae [ 	]*MOVE  @BP\[\-\-OFFS\], IMR
 314:	88 ae [ 	]*MOVE  @BP\[\-\-OFFS\], SC
 316:	b8 ae [ 	]*MOVE  @BP\[\-\-OFFS\], IIR
 318:	e8 ae [ 	]*MOVE  @BP\[\-\-OFFS\], CKCN
 31a:	f8 ae [ 	]*MOVE  @BP\[\-\-OFFS\], WDCN
 31c:	09 ae [ 	]*MOVE  @BP\[\-\-OFFS\], A\[0\]
 31e:	f9 ae [ 	]*MOVE  @BP\[\-\-OFFS\], A\[15\]
 320:	0a ae [ 	]*MOVE  @BP\[\-\-OFFS\], ACC
 322:	1a ae [ 	]*MOVE  @BP\[\-\-OFFS\], A\[AP\]
 324:	0c ae [ 	]*MOVE  @BP\[\-\-OFFS\], IP
 326:	1d ae [ 	]*MOVE  @BP\[\-\-OFFS\], SP
 328:	2d ae [ 	]*MOVE  @BP\[\-\-OFFS\], IV
 32a:	6d ae [ 	]*MOVE  @BP\[\-\-OFFS\], LC\[0\]
 32c:	7d ae [ 	]*MOVE  @BP\[\-\-OFFS\], LC\[1\]
 32e:	3e ae [ 	]*MOVE  @BP\[\-\-OFFS\], OFFS
 330:	4e ae [ 	]*MOVE  @BP\[\-\-OFFS\], DPC
 332:	5e ae [ 	]*MOVE  @BP\[\-\-OFFS\], GR
 334:	6e ae [ 	]*MOVE  @BP\[\-\-OFFS\], GRL
 336:	7e ae [ 	]*MOVE  @BP\[\-\-OFFS\], BP
 338:	8e ae [ 	]*MOVE  @BP\[\-\-OFFS\], GRS
 33a:	9e ae [ 	]*MOVE  @BP\[\-\-OFFS\], GRH
 33c:	ae ae [ 	]*MOVE  @BP\[\-\-OFFS\], GRXL
 33e:	be ae [ 	]*MOVE  @BP\[\-\-OFFS\], FP
 340:	0f ae [ 	]*MOVE  @BP\[\-\-OFFS\], @DP\[0\]
 342:	4f ae [ 	]*MOVE  @BP\[\-\-OFFS\], @DP\[1\]
 344:	01 3e [ 	]*MOVE  OFFS, #01h
 346:	08 be [ 	]*MOVE  OFFS, AP
 348:	18 be [ 	]*MOVE  OFFS, APC
 34a:	48 be [ 	]*MOVE  OFFS, PSF
 34c:	58 be [ 	]*MOVE  OFFS, IC
 34e:	68 be [ 	]*MOVE  OFFS, IMR
 350:	88 be [ 	]*MOVE  OFFS, SC
 352:	b8 be [ 	]*MOVE  OFFS, IIR
 354:	e8 be [ 	]*MOVE  OFFS, CKCN
 356:	f8 be [ 	]*MOVE  OFFS, WDCN
 358:	09 be [ 	]*MOVE  OFFS, A\[0\]
 35a:	f9 be [ 	]*MOVE  OFFS, A\[15\]
 35c:	0a be [ 	]*MOVE  OFFS, ACC
 35e:	1a be [ 	]*MOVE  OFFS, A\[AP\]
 360:	0c be [ 	]*MOVE  OFFS, IP
 362:	0d be [ 	]*MOVE  OFFS, @SP\-\-
 364:	1d be [ 	]*MOVE  OFFS, SP
 366:	2d be [ 	]*MOVE  OFFS, IV
 368:	6d be [ 	]*MOVE  OFFS, LC\[0\]
 36a:	7d be [ 	]*MOVE  OFFS, LC\[1\]
 36c:	4e be [ 	]*MOVE  OFFS, DPC
 36e:	5e be [ 	]*MOVE  OFFS, GR
 370:	6e be [ 	]*MOVE  OFFS, GRL
 372:	7e be [ 	]*MOVE  OFFS, BP
 374:	8e be [ 	]*MOVE  OFFS, GRS
 376:	9e be [ 	]*MOVE  OFFS, GRH
 378:	ae be [ 	]*MOVE  OFFS, GRXL
 37a:	be be [ 	]*MOVE  OFFS, FP
 37c:	0f be [ 	]*MOVE  OFFS, @DP\[0\]
 37e:	4f be [ 	]*MOVE  OFFS, @DP\[1\]
 380:	1f be [ 	]*MOVE  OFFS, @DP\[0\]\+\+
 382:	5f be [ 	]*MOVE  OFFS, @DP\[1\]\+\+
 384:	2f be [ 	]*MOVE  OFFS, @DP\[0\]\-\-
 386:	6f be [ 	]*MOVE  OFFS, @DP\[1\]\-\-
