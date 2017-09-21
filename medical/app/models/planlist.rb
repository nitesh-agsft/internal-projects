class Planlist < ApplicationRecord
    validates_presence_of :planname, :message => "Planname cant be left blank"
    validates_presence_of :planid, :message => "ID can't be left blank"
    
end
