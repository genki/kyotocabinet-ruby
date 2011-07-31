require 'kyotocabinet'
include KyotoCabinet

# process the database by iterator
DB::process('casket.kch') { |db|

  # set the encoding of external strings
  db.set_encoding('utf-8')

  # store records
  db['foo'] = 'hop';  # string is fundamental
  db[:bar] = 'step';  # symbol is also ok
  db[3] = 'jump';     # number is also ok

  # retrieve a record value
  printf("%s\n", db['foo'])

  # update records in transaction
  db.transaction {
    db['foo'] = 2.71828
    true
  }

  # multiply a record value
  db.accept('foo') { |key, value|
    value.to_f * 2
  }

  # traverse records by iterator
  db.each { |key, value|
    printf("%s:%s\n", key, value)
  }

  # upcase values by iterator
  db.iterate { |key, value|
    value.upcase
  }

  # traverse records by cursor
  db.cursor_process { |cur|
    cur.jump
    while cur.accept { |key, value|
        printf("%s:%s\n", key, value)
        Visitor::NOP
      }
      cur.step
    end
  }

}
