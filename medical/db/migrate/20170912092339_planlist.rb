class Planlist < ActiveRecord::Migration[5.1]
  def self.up
      create_table :planlists do |t|
          t.column :planid, :integer, :null => false
          t.column :planname, :string, :null => false
      end
  end
  def self.down
      drop_table :planlists
  end      
    
end
