require 'rubygems'

Gem::Specification.new do |s|
    s.name          = 'xftdim'
    s.version       = '0.0.1'
    s.author        = 'shura'
    s.email         = 'shura1991@gmail.com'
    s.homepage      = 'http://github.com/shurizzle/ruby-xftdim'
    s.platform      = Gem::Platform::RUBY
    s.summary       = 'Get dimensions of string for a xft-font'
    s.description   = 'Add a method to String:Class to get width and height of text for given string and xft-font'
    s.files         = Dir['ext/*']
    s.extensions    = 'ext/extconf.rb'
    s.has_rdoc      = true
end
