#!/opt/gnu/bin/perl

@toto=`ls -1t *.c`;
foreach $name (@toto) {
  chop $name;
  $ret=open(FILEIN,"< $name");
  $ret=open(FILEOUT,"> $name.new");
  while (<FILEIN>) {
	  $_ =~ s/$ARGV[0]/$ARGV[1]/g;
	  print FILEOUT $_;
  }
  system("mv $name.new $name");
}
