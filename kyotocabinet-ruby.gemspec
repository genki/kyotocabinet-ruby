# -*- encoding: utf-8 -*-
$:.push File.expand_path("../lib", __FILE__)
require "kyotocabinet-ruby/version"

Gem::Specification.new do |s|
  s.name        = "kyotocabinet-ruby"
  s.version     = Kyotocabinet::Ruby::VERSION
  s.platform    = Gem::Platform::RUBY
  s.authors     = ["FAL Labs"]
  s.email       = ["info@fallabs.com"]
  s.homepage    = "http://fallabs.com/Kyotocabinet/"
  s.summary = "Kyoto Cabinet: a straightforward implementation of DBM."
  s.description = "Kyoto Cabinet is a library of routines for managing a database.  The database is a simple data file containing records, each is a pair of a key and a value.  Every key and value is serial bytes with variable length.  Both binary data and character string can be used as a key and a value.  Each key must be unique within a database.  There is neither concept of data tables nor data types.  Records are organized in hash table or B+ tree."

  s.rubyforge_project = "kyotocabinet-ruby"

  s.files         = `git ls-files`.split("\n")
  s.test_files    = `git ls-files -- {test,spec,features}/*`.split("\n")
  s.executables   = `git ls-files -- bin/*`.split("\n").map{ |f| File.basename(f) }
  s.require_paths = ["lib"]
end
