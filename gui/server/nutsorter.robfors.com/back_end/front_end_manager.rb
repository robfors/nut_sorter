# this class keeps track of all the front_ends and distributes any update
#   to all of the front_ends

class FontEndManager
  
  @front_ends = []
  
  NutSorter.on(:small_steel_nut_count_updated) { update_small_steel_nut_count }
  NutSorter.on(:big_brass_nut_count_updated) { update_big_brass_nut_count }
  NutSorter.on(:big_nylon_nut_count_updated) { update_big_nylon_nut_count }
  NutSorter.on(:small_brass_nut_count_updated) { update_small_brass_nut_count }
  NutSorter.on(:coin_count_updated) { update_coin_count }
  NutSorter.on(:status_updated) { update_status }
  
  def self.add(front_end)
    @front_ends.push(front_end)

    front_end.update_small_steel_nut_count(NutSorter.small_steel_nut_count)
    front_end.update_big_brass_nut_count(NutSorter.big_brass_nut_count)
    front_end.update_big_nylon_nut_count(NutSorter.big_nylon_nut_count)
    front_end.update_small_brass_nut_count(NutSorter.small_brass_nut_count)
    front_end.update_coin_count(NutSorter.coin_count)
    front_end.update_status(NutSorter.status)
  end
  
  def self.update_small_steel_nut_count
    @front_ends.each do |front_end|
      begin
        front_end.update_small_steel_nut_count(NutSorter.small_steel_nut_count)
      rescue Reel::SocketError
        @front_ends.delete(front_end)
      end
    end
  end
  
  def self.update_big_brass_nut_count
    @front_ends.each do |front_end|
      begin
        front_end.update_big_brass_nut_count(NutSorter.big_brass_nut_count)
      rescue Reel::SocketError
        @front_ends.delete(front_end)
      end
    end
  end
  
  def self.update_big_nylon_nut_count
    @front_ends.each do |front_end|
      begin
        front_end.update_big_nylon_nut_count(NutSorter.big_nylon_nut_count)
      rescue Reel::SocketError
        @front_ends.delete(front_end)
      end
    end
  end
  
  def self.update_small_brass_nut_count
    @front_ends.each do |front_end|
      begin
        front_end.update_small_brass_nut_count(NutSorter.small_brass_nut_count)
      rescue Reel::SocketError
        @front_ends.delete(front_end)
      end
    end
  end
  
  def self.update_coin_count
    @front_ends.each do |front_end|
      begin
        front_end.update_coin_count(NutSorter.coin_count)
      rescue Reel::SocketError
        @front_ends.delete(front_end)
      end
    end
  end
  
  def self.update_status
    @front_ends.each do |front_end|
      begin
        front_end.update_status(NutSorter.status)
      rescue Reel::SocketError
        @front_ends.delete(front_end)
      end
    end
  end
  
end
