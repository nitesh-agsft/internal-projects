class Customer < ApplicationRecord
    #belongs_to :account
    validates_presence_of :plans, :message =>"Plan id Cant be empty" 
    validates_presence_of :planname, :message => "Planname Cant be empty" 
    validates_presence_of :account_no, :message => "Account no. cant be empty" 
    validates_presence_of :paytype, :message => "Select Pay type" 
    validates_presence_of :plantype, :message => "Select Plan type" 
    validates_presence_of :accountingmethod, :message => "Specify accounting method" 
    validates_presence_of :hohpresent, :message => "HeadofHouse is registered??" 
    validates_numericality_of :account_no, :message => "Account No. should be numeric in nature"
    validates_length_of :account_no, :minimum => 5, :maximum => 5, :allow_blank => false, :message => "Account no length should be equal to 5 digit only" 
end
