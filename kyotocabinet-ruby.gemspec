# -*- encoding: utf-8 -*-
Gem::Specification.new do |s|
  s.name        = "kyotocabinet-ruby"
  s.version     = "1.27"
  s.platform    = Gem::Platform::RUBY
  s.authors     = ["FAL Labs"]
  s.email       = ["info@fallabs.com"]
  s.homepage    = "http://fallabs.com/kyotocabinet/"
  s.summary     = "Kyoto Cabinet: a straightforward implementation of DBM."
  s.description = (<<EOH).split("\n").join(' ')
Kyoto Cabinet is a library of routines for managing a database.  The database
is a simple data file containing records, each is a pair of a key and a value.
Every key and value is serial bytes with variable length.  Both binary data and
character string can be used as a key and a value.  Each key must be unique
within a database.  There is neither concept of data tables nor data types.
Records are organized in hash table or B+ tree.
EOH
  s.rubyforge_project = "kyotocabinet-ruby"
  s.files         = ['extconf.rb', 'kyotocabinet.cc']
  s.extensions    << 'extconf.rb'
end
