class PlanlistController < ApplicationController
    layout 'standard'
    
    def update
        @plupdate = Planlist.find(params[:id])
        if @plupdate.update_attributes(updateattributes)
            redirect_to :action => 'list'
        else
            render_to :action => 'edit'
        end        
    end
    
    def edit
        @pledit = Planlist.find(params[:id])        
    end
    
    def create
        
    end
    
    def delete
        Planlist.find(params[:id]).destroy        
    end
    
    def new
        @plnew = Planlist.new
    end
    
    def list
        @pllist = Planlist.all        
    end
    
end
