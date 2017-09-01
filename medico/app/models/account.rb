class Account < ActiveRecord::Base
    belongs_to :customer
    validates_presence_of :lastname
    validates_presence_of :firstname
    validates_presence_of :gender
    validates_presence_of :birthdate
    validates_numericality_of :birthdate
    validates_numericality_of :account_no,:message =>"Error only numerical value is needed"
end
