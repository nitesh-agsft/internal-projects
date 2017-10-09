class CreateAlotdevices < ActiveRecord::Migration
  def self.up
    create_table :alotdevices do |t|
        t.column :empid, :string, :null => false
        t.column :empfn, :string, :null => false
        t.column :empln, :string, :null => false
        t.column :machineid, :string, :null => false
        t.column :monitorid, :string, :null => false
        t.column :mouseid, :string, :null => false
        t.column :keyboardid, :string, :null => false
        t.column :adaptorid, :string, :null => false      

      t.timestamps null: false
    end
  end
 def self.down
     drop_table :alotdevices
 end
end
