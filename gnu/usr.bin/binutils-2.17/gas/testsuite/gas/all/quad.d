#objdump : -s -j .data -j "\$DATA\$"
#name : .quad tests

.*: .*

Contents of section (\.data|\$DATA\$):
 0000 (00000000 76543210 00000000 80000000|10325476 00000000 00000080 00000000|00000000 54761032 00000000 00800000|32107654 00000000 00008000 00000000) .*
 00.. (00000000 87654321 00000000 ffffffff|21436587 00000000 ffffffff 00000000|00000000 65872143 00000000 ffffffff|43218765 00000000 ffffffff 00000000) .*
 00.. (ffffffff 89abcdf0 ffffffff 80000000|f0cdab89 ffffffff 00000080 ffffffff|ffffffff ab89f0cd ffffffff 00800000|cdf089ab ffffffff 00008000 ffffffff) .*
 00.. (ffffffff 789abcdf ffffffff 00000001|dfbc9a78 ffffffff 01000000 ffffffff|ffffffff 9a78dfbc ffffffff 00000100|bcdf789a ffffffff 00010000 ffffffff) .*
 00.. (01234567 89abcdef fedcba98 76543211|efcdab89 67452301 11325476 98badcfe|23016745 ab89efcd dcfe98ba 54761132|cdef89ab 45670123 32117654 ba98fedc) .*
#pass
