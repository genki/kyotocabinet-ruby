require 'kyotocabinet'
include KyotoCabinet

# create the database object
db = DB::new

# open the database
unless db.open('casket.kch', DB::OWRITER | DB::OCREATE)
  STDERR.printf("open error: %s\n", db.error)
end

# store records
unless db.set('foo', 'hop') and
    db.set('bar', 'step') and
    db.set('baz', 'jump')
  STDERR.printf("set error: %s\n", db.error)
end

# retrieve records
value = db.get('foo')
if value
  printf("%s\n", value)
else
  STDERR.printf("get error: %s\n", db.error)
end

# traverse records
cur = db.cursor
cur.jump
while rec = cur.get(true)
  printf("%s:%s\n", rec[0], rec[1])
end
cur.disable

# close the database
unless db.close
  STDERR.printf("close error: %s\n", db.error)
end
