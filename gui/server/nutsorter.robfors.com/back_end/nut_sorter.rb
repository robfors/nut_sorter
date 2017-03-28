# this class keeps track of the status and counters of the nut sorter

class NutSorter
  extend Eventable
  
  @small_steel_nut_count = 0
  @big_brass_nut_count = 0
  @big_nylon_nut_count = 0
  @small_brass_nut_count = 0
  @coin_count = 0
  @status = "Offline"

  class << self
    attr_reader :small_steel_nut_count, :big_brass_nut_count, 
      :big_nylon_nut_count, :small_brass_nut_count, :coin_count, :status
  end
  
  def self.update_small_steel_nut_count(count)
    @small_steel_nut_count = count
    trigger(:small_steel_nut_count_updated)
  end
  
  def self.update_big_brass_nut_count(count)
    @big_brass_nut_count = count
    trigger(:big_brass_nut_count_updated)
  end
  
  def self.update_big_nylon_nut_count(count)
    @big_nylon_nut_count = count
    trigger(:big_nylon_nut_count_updated)
  end
  
  def self.update_small_brass_nut_count(count)
    @small_brass_nut_count = count
    trigger(:small_brass_nut_count_updated)
  end
  
  def self.update_coin_count(count)
    @coin_count = count
    trigger(:coin_count_updated)
  end
    
  def self.update_status(status)
    @status = status
    trigger(:status_updated)
  end
  
end
