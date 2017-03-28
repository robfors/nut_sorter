# this class represents a browser that has connected and waiting for
#   update about the nut sorter
# many of these front ends may exist simultaneously

class FrontEnd

  def initialize(websocket)
    @websocket = websocket
  end
  
  def update_small_steel_nut_count(count)
    @websocket.write("update_small_steel_nut_count:#{count.to_s}")
  end
  
  def update_big_brass_nut_count(count)
    @websocket.write("update_big_brass_nut_count:#{count.to_s}")
  end
  
  def update_big_nylon_nut_count(count)
    @websocket.write("update_big_nylon_nut_count:#{count.to_s}")
  end
  
  def update_small_brass_nut_count(count)
    @websocket.write("update_small_brass_nut_count:#{count.to_s}")
  end
  
  def update_coin_count(count)
    @websocket.write("update_coin_count:#{count.to_s}")
  end
  
  def update_status(status)
    @websocket.write("update_status:#{status}")
  end
  
end
