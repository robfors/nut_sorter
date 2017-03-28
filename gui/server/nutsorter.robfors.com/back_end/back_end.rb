# this class sets up a server that waits for new connections from browsers
# a new connection with be converted into a front_end object and added to the
#   font_end_manager

class BackEnd < Reel::Server::HTTP
  include Celluloid::Logger

  def initialize
    info "Back End starting..."
    super("0.0.0.0", 9998, &method(:on_connection))
  end

  def on_connection(connection)
    connection.each_request do |request|
      if request.websocket?
        info "Browser connected."
        websocket = request.websocket
        if websocket.url == "/"
          front_end = FrontEnd.new(websocket)
          FontEndManager.add(front_end)
          connection.detach
        else
          websocket.close
        end
        nil
      else
        request.respond :not_found, "Not Found"
      end
    end
  end
  
end
