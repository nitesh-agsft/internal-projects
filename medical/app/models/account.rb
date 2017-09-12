class Account < ApplicationRecord
    has_many :customers
    attribute :birthdate, :date
    validates_presence_of :firstname
    validates_presence_of :lastname
    validates_presence_of :birthdate
    validates_presence_of :gender
    validates_presence_of :account_no
    validates_numericality_of :account_no
end
