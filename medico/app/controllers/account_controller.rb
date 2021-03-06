class AccountController < ApplicationController
    layout 'standard'
    def update
        @account = Account.find(params[:id])
        if @account.update_attributes(account_params)
            redirect_to :action => "show", :id => @account
        else
            @customer = Customer.all
            render :action => "edit"
        end
    end

    def create
        @account = Account.new(account_params)
        puts params[:firstname]
        if @account.save
            redirect_to :action => "view"
        else
            render :action => "new"
        end
    end

    def edit
        @account = Account.find(params[:id])
        @customer = Customer.all
    end

    def new 
        @account = Account.new
        
        @customer = Customer.all
    end

    def show 
        @account = Account.find(param[:id])
    end
    def view
        @account = Account.all
    end
    def auto_assign
        @maxaccount = Account.maximum("account_no")
        Rails.logger.debug("debug::" + "@maxaccount")
        #return render 'auto_assign'
    end

    def account_params
        params.require(:account).permit(:account_no, :lastname, :firstname, :gender, :birthdate, :headofhouse, :middlename)
    end
end
