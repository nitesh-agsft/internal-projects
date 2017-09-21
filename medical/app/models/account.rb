class Account < ApplicationRecord
    #has_many :customers
    attribute :birthdate, :date
    validates_presence_of :firstname, :message => "Firstname Cant be empty"
    validates_presence_of :lastname, :message => "Lastname Cant be empty" 
    validates_presence_of :birthdate, :message => "Birthdate Cant be empty" 
    validates_presence_of :gender
    validates_presence_of :account_no, :message => "Account No. Cant be empty" 
    validates_numericality_of :account_no, :message => "Account No. should be numeric in nature"
    validates_length_of :account_no, :minimum => 5, :maximum => 5, :allow_blank => false, :message => "Account no should be of 5 digits" 
end
