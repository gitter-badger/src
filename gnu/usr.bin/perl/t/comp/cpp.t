#!./perl

# $RCSfile: cpp.t,v $$Revision: 4.1 $$Date: 92/08/07 18:27:18 $

BEGIN {
    chdir 't' if -d 't';
    @INC = '../lib';
}

use Config;
if ( ($Config{'cppstdin'} =~ /\bcppstdin\b/) and
     ( ! -x $Config{'scriptdir'} . "/cppstdin") ) {
    print "1..0\n";
    exit; 		# Cannot test till after install, alas.
}

system "./perl -P comp/cpp.aux"
