class PlanlistController < ApplicationController
    layout 'standard'
    
    def update
        @planlist = Planlist.find(params[:id])
        if @planlist.update_attributes(updateattributes)
            redirect_to :action => 'new'
        else
            render_to :action => 'new'
        end        
    end
    
    def edit
        @planlist = Planlist.find(params[:id])        
    end
    
    def create
        @planlist = Planlist.new(createparams)
        if @planlist.save
            redirect_to :action => 'new'
        else
            puts "sorry error"
        end
    end
    
    def createparams
        params.require(:planlists).permit(:planid, :planname)
    end
    
    def delete
        Planlist.find(params[:id]).destroy
        redirect_to :action => "new"
    end
    
    def new
        @planlist = Planlist.new
        @planlistm = Planlist.all
        
    end
    
    def list
                
    end
    
end
