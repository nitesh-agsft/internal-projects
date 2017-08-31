class Customer < ActiveRecord::Base
    validates_numericality_of :plans
    validates_numericality_of :account_no
end
