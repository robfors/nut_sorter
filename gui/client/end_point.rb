# run this script on the computer that is connected to the Arduino over serial
# the computer must also have an internet connection

require 'socket'
require 'serialport'

socket = TCPSocket.new('robfors.com', 9997)

#test with a network socket when we dont have the Arduino around
#server = TCPServer.new 2000
#serial = server.accept
serial = SerialPort.new "/dev/ttyACM0", 9600

small_steel_nut_count = 0
big_brass_nut_count = 0
big_nylon_nut_count = 0
small_brass_nut_count = 0
coin_count = 0

loop do
  message = serial.gets

  case message.strip
  when "|reset"
    small_steel_nut_count = 0
    socket.puts "update_small_steel_nut_count:#{0}"
    big_brass_nut_count = 0
    socket.puts "update_big_brass_nut_count:#{0}"
    big_nylon_nut_count = 0
    socket.puts "update_big_nylon_nut_count:#{0}"
    small_brass_nut_count = 0
    socket.puts "update_small_brass_nut_count:#{0}"
    coin_count = 0
    socket.puts "update_coin_count:#{0}"
  when "|calibrating"
    socket.puts "update_status:Calibrating..."
  when "|running"
    socket.puts "update_status:Online"
  when "|setup_error"
    socket.puts "update_status:Setup Error!"
  when "|small_steel_nut"
    small_steel_nut_count += 1
    socket.puts "update_small_steel_nut_count:#{small_steel_nut_count}"
  when "|big_brass_nut"
    big_brass_nut_count += 1
    socket.puts "update_big_brass_nut_count:#{big_brass_nut_count}"
  when "|big_nylon_nut"
    big_nylon_nut_count += 1
    socket.puts "update_big_nylon_nut_count:#{big_nylon_nut_count}"
  when "|small_brass_nut"
    small_brass_nut_count += 1
    socket.puts "update_small_brass_nut_count:#{small_brass_nut_count}"
  when "|coin"
    coin_count += 1
    socket.puts "update_coin_count:#{coin_count}"
  end

end

socket.close
