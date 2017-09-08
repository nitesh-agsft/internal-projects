class Customers < ActiveRecord::Migration[5.1]
  def self.up
      create_table :customers do |t|
          t.column :plans, :string, :null => false
          t.column :planname, :string, :null => false
          t.column :account_no, :string, :null => false
          t.column :paytype, :string, :null =>false
          t.column :plantype, :string, :null => false
          t.column :accountingmethod, :string, :null => false
          t.column :hohpresent, :string, :null => false
          t.column :headofhouseaccn, :string, :null => true
          t.timestamp
      end
  end
  def self.down
      drop_table :customers
  end
      
end
