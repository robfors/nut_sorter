# this class represents a client that connects and starts sending updates
#  about the nut sorter

require 'celluloid/current'
require 'celluloid/io'

class MatchData
  def to_h
    names.zip(captures).to_h
  end
end

class NutSorterClient
  include Celluloid
  
  finalizer :shutdown

  def initialize
    puts "Nut sorter client started"
    @server = TCPServer.new("0.0.0.0", 9997)
    async.run
  end

  def shutdown
    @server.close if @server
  end

  def run
    loop do
      handle_connection(@server.accept)
    end
  end
  
  def handle_connection(socket)
    loop do
      begin
        message = socket.gets
        if message.nil?
          socket.close
          return
        end
        handle_message(message)
      rescue EOFError
        socket.close
        return
      end
    end
  end
  
  def handle_message(message)
    return unless message.is_a?(String)
    key = message.match(/^(?<key>[^:]+):(?<value>.+)/).to_h["key"]
    value = message.match(/^(?<key>[^:]+):(?<value>.+)/).to_h["value"]

    case key
    when "update_small_steel_nut_count"
      NutSorter.update_small_steel_nut_count(value.to_i)
    when "update_big_brass_nut_count"
      NutSorter.update_big_brass_nut_count(value.to_i)
    when "update_big_nylon_nut_count"
      NutSorter.update_big_nylon_nut_count(value.to_i)
    when "update_small_brass_nut_count"
      NutSorter.update_small_brass_nut_count(value.to_i)
    when "update_coin_count"
      NutSorter.update_coin_count(value.to_i)
    when "update_status"
      NutSorter.update_status(value)
    end
    
  end

end
