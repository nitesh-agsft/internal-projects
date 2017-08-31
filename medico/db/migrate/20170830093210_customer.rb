class Customer < ActiveRecord::Migration
  def self.up
    create_table :customer do |t|
      t.column :plans, :integer, :null => false
      t.column :account_no, :integer, :null => false
      t.column :plan_name, :string , :null => false
      t.column :pay_type, :integer, :null => false
      t.column :plan_type, :string, :null => false
      t.column :accounting_method, :string, :null => false
    end
  end

  def self.down
    drop_table :customer
  end
end
