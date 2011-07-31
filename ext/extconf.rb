require "mkmf"

File::unlink("Makefile") if (File::exist?("Makefile"))
dir_config('kyotocabinet')

home = ENV["HOME"]
ENV["PATH"] = ENV["PATH"] + ":/usr/local/bin:$home/bin:."
kccflags = `kcutilmgr conf -i 2>/dev/null`.chomp
kcldflags = `kcutilmgr conf -l 2>/dev/null`.chomp
kcldflags = kcldflags.gsub(/-l[\S]+/, "").strip
kclibs = `kcutilmgr conf -l 2>/dev/null`.chomp
kclibs = kclibs.gsub(/-L[\S]+/, "").strip

kccflags = "-I/usr/local/include" if(kccflags.length < 1)
kcldflags = "-L/usr/local/lib" if(kcldflags.length < 1)
kclibs = "-lkyotocabinet -lz -lstdc++ -lrt -lpthread -lm -lc" if(kclibs.length < 1)

Config::CONFIG["CPP"] = "g++ -E"
$CFLAGS = "-I. #{kccflags} -Wall #{$CFLAGS} -O2"
$LDFLAGS = "#{$LDFLAGS} -L. #{kcldflags}"
$libs = "#{$libs} #{kclibs}"

printf("setting variables ...\n")
printf("  \$CFLAGS = %s\n", $CFLAGS)
printf("  \$LDFLAGS = %s\n", $LDFLAGS)
printf("  \$libs = %s\n", $libs)

if have_header('kccommon.h')
  create_makefile('kyotocabinet')
end
