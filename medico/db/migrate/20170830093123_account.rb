class Account < ActiveRecord::Migration
  def self.up
    create_table :accounts do |t|
      t.column :account_no, :integer, :null => false
      t.column :lastname, :string, :limit => 32, :null => false
      t.column :firstname, :string, :null => false
      t.column :middlename, :string, :null => true
      t.column :gender, :string, :null => false
      t.column :birthdate, :string, :null => false
      t.column :headofhouse, :string,:null => true
      t.column :account_created_at, :timestamp

    end
  end

  def self.down
    drop_table :accounts
  end
end
