require 'rubygems'
require 'rake'
require 'rake/extensiontask'
require 'bundler'

Rake::ExtensionTask.new 'kyotocabinet' do |ext|
  ext.ext_dir = 'ext'
end

#task :build => [:clean, :compile]

Bundler::GemHelper.install_tasks
