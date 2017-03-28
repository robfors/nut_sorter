# run this file on a public facing server

require 'pry'
require 'reel'
require 'celluloid/autostart'

require_relative 'eventable.rb'
require_relative 'nut_sorter.rb'

require_relative 'back_end.rb'
require_relative 'front_end.rb'
require_relative 'front_end_manager.rb'
require_relative 'nut_sorter_client.rb'

puts "Started..."



NutSorterClient.supervise_as :nut_sorter_client
BackEnd.supervise_as :back_end
#BackEnd.new
#display_manager = DisplayManager.instance

#binding.pry
sleep
