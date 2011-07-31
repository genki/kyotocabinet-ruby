require 'kyotocabinet'
include KyotoCabinet

# create the database object
db = DB::new

# open the database
unless db.open('casket.kch', DB::OREADER)
  STDERR.printf("open error: %s\n", db.error)
end

# define the visitor
class VisitorImpl < Visitor
  # call back function for an existing record
  def visit_full(key, value)
    printf("%s:%s\n", key, value)
    return NOP
  end
  # call back function for an empty record space
  def visit_empty(key)
    STDERR.printf("%s is missing\n", key)
    return NOP
  end
end
visitor = VisitorImpl::new

# retrieve a record with visitor
unless db.accept("foo", visitor, false) and
    db.accept("dummy", visitor, false)
  STDERR.printf("accept error: %s\n", db.error)
end

# traverse records with visitor
unless db.iterate(visitor, false)
  STDERR.printf("iterate error: %s\n", db.error)
end

# close the database
unless db.close
  STDERR.printf("close error: %s\n", db.error)
end
