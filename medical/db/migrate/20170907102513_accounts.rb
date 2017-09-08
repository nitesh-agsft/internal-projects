class Accounts < ActiveRecord::Migration[5.1]
  def self.up
      create_table :accounts do |t|
          t.column :lastname, :string, :null => false
          t.column :firstname, :string, :null => false
          t.column :middlename, :string, :null => true
          t.column :gender, :string, :null => false
          t.column :birthdate, :string, :null => false
          t.column :headofhouse, :string, :null => false
          t.column :account_no, :integer, :null => false
          t.timestamp
      end
  end
  def self.down
      drop_table :accounts
  end
end
