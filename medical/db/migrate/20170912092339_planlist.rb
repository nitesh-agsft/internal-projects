class Planlist < ActiveRecord::Migration[5.1]
  def self.up
      create_table :planlists do |t|
          t.column :planid
          t.column :planname
      end
  end
  def self.down
      drop_table :planlists
  end      
    
end
