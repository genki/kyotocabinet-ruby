require 'rubygems'
require 'rake'
require 'rake/extensiontask'
require 'bundler'

Rake::ExtensionTask.new('kyotocabinet'){|ext| ext.ext_dir = '.'}

task :build => [:clean, :compile]

Bundler::GemHelper.install_tasks
