class Customer < ApplicationRecord
    has_one :account
    validates_presence_of :plans
    validates_presence_of :planname
    validates_presence_of :account_no
    validates_presence_of :paytype
    validates_presence_of :plantype
    validates_presence_of :accountingmethod
    validates_presence_of :hohpresent
    validates_numericality_of :account_no
end
