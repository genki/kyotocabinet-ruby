require 'kyotocabinet'
include KyotoCabinet

def memoryusage()
  rss = -1
  file = open('/proc/self/status')
  file.each do |line|
    if line =~ /^VmRSS:/
      line.gsub!(/.*:\s*(\d+).*/, '\1')
      rss = line.to_i / 1024.0
      break
    end
  end
  return rss
end

GC.start
musage = memoryusage
rnum = 1000000
if ARGV.length > 0
  rnum = ARGV[0].to_i
end

if ARGV.length > 1
  hash = DB::new
  hash.open(ARGV[1], DB::OWRITER | DB::OCREATE | DB::OTRUNCATE) || raise("open failed")
else
  hash = Hash.new
end

stime = Time.now
(0...rnum).each do |i|
  key = sprintf("%08d", i)
  value = sprintf("%08d", i)
  hash[key] = value
end
etime = Time.now
GC.start

printf("Count: %d\n", hash.count)
printf("Time: %.3f sec.\n", etime - stime)
printf("Usage: %.3f MB\n", memoryusage - musage)
