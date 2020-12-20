#ifndef GMCSDK_DEF_H
#define GMCSDK_DEF_H


const unsigned int LEN_ID = 64;
const unsigned int LEN_NAME = 64;
const unsigned int LEN_SYMBOL = 32;
const unsigned int LEN_INFO = 128;
const unsigned int LEN_EXCHANGE = 8;
const unsigned int LEN_ISO_DATATIME = 36;
const unsigned int LEN_FREQUENCY = 8;
const unsigned int DEPTH_OF_QUOTE = 10;
const unsigned int LEN_PARAM = 256;
const unsigned int LEN_COMMENT = 256;
const unsigned int LEN_MAX_ORDER_QUEUE = 50;
const unsigned int LEN_TYPE = 8;

enum StrategyMode
{
	MODE_UNDEF = 0,          //δ���壬 ���Բ�������
	MODE_LIVE = 1,           //ʵ�������ģʽ
	MODE_BACKTEST = 2        //�ز�ģʽ
};

enum OrderStatus
{
	OrderStatus_Unknown = 0,
	OrderStatus_New = 1,                   //�ѱ�
	OrderStatus_PartiallyFilled = 2,       //����
	OrderStatus_Filled = 3,                //�ѳ�
	OrderStatus_DoneForDay = 4,            //
	OrderStatus_Canceled = 5,              //�ѳ�
	OrderStatus_PendingCancel = 6,         //����
	OrderStatus_Stopped = 7,               //
	OrderStatus_Rejected = 8,              //�Ѿܾ�
	OrderStatus_Suspended = 9,             //����
	OrderStatus_PendingNew = 10,           //����
	OrderStatus_Calculated = 11,           //
	OrderStatus_Expired = 12,              //�ѹ���
	OrderStatus_AcceptedForBidding = 13,   //
	OrderStatus_PendingReplace = 14,       //
};

//ִ�лر�����
enum ExecType
{
	ExecType_Unknown = 0,
	ExecType_New = 1,                      //�ѱ�
	ExecType_DoneForDay = 4,               //
	ExecType_Canceled = 5,                 //�ѳ���
	ExecType_PendingCancel = 6,            //������
	ExecType_Stopped = 7,                  //
	ExecType_Rejected = 8,                 //�Ѿܾ�
	ExecType_Suspended = 9,                //����
	ExecType_PendingNew = 10,              //����
	ExecType_Calculated = 11,              //
	ExecType_Expired = 12,                 //����
	ExecType_Restated = 13,                //
	ExecType_PendingReplace = 14,          //
	ExecType_Trade = 15,                   //�ɽ�
	ExecType_TradeCorrect = 16,            //
	ExecType_TradeCancel = 17,             //
	ExecType_OrderStatus = 18,             //ί��״̬
	ExecType_CancelRejected = 19,          //�������ܾ�
};

//ί�оܾ�ԭ��
enum OrderRejectReason
{
	OrderRejectReason_Unknown = 0,                           //δ֪ԭ��
	OrderRejectReason_RiskRuleCheckFailed = 1,               //�����Ϸ�ع��� 
	OrderRejectReason_NoEnoughCash = 2,                      //�ʽ���
	OrderRejectReason_NoEnoughPosition = 3,                  //��λ����
	OrderRejectReason_IllegalAccountId = 4,                  //�Ƿ��˻�ID
	OrderRejectReason_IllegalStrategyId = 5,                 //�Ƿ�����ID
	OrderRejectReason_IllegalSymbol = 6,                     //�Ƿ����״���
	OrderRejectReason_IllegalVolume = 7,                     //�Ƿ�ί����
	OrderRejectReason_IllegalPrice = 8,                      //�Ƿ�ί�м�
	OrderRejectReason_AccountDisabled = 10,                  //�����˺ű���ֹ����
	OrderRejectReason_AccountDisconnected = 11,              //�����˺�δ����
	OrderRejectReason_AccountLoggedout = 12,                 //�����˺�δ��¼
	OrderRejectReason_NotInTradingSession = 13,              //�ǽ���ʱ��
	OrderRejectReason_OrderTypeNotSupported = 14,            //ί�����Ͳ�֧��
	OrderRejectReason_Throttle = 15,                         //��������
	OrderRejectReason_SymbolSusppended = 16,                 //���״���ͣ��
	OrderRejectReason_Internal = 999,                        //�ڲ�����

	CancelOrderRejectReason_OrderFinalized = 101,            //ί�������
	CancelOrderRejectReason_UnknownOrder = 102,              //δ֪ί��
	CancelOrderRejectReason_BrokerOption = 103,              //��̨����
	CancelOrderRejectReason_AlreadyInPendingCancel = 104,    //ί�г�����
};

//ί�з���
enum OrderSide
{
	OrderSide_Unknown = 0,
	OrderSide_Buy = 1,    //����
	OrderSide_Sell = 2,    //����
};

//ί������
enum OrderType
{
	OrderType_Unknown = 0,
	OrderType_Limit = 1,    //�޼�ί��
	OrderType_Market = 2,    //�м�ί��
	OrderType_Stop = 3,    //ֹ��ֹӯί��
};

//ί��ʱ������
enum OrderDuration
{
	OrderDuration_Unknown = 0,
	OrderDuration_FAK = 1,  //��ʱ�ɽ�ʣ�೷��(fill and kill)
	OrderDuration_FOK = 2,  //��ʱȫ��ɽ�����(fill or kill)
	OrderDuration_GFD = 3,  //������Ч(good for day)
	OrderDuration_GFS = 4,  //������Ч(good for section)
	OrderDuration_GTD = 5,  //ָ������ǰ��Ч(goodl till date)
	OrderDuration_GTC = 6,  //����ǰ��Ч(good till cancel)
	OrderDuration_GFA = 7,  //���Ͼ���ǰ��Ч(good for auction)
};

//ί�гɽ�����
enum OrderQualifier
{
	OrderQualifier_Unknown = 0,
	OrderQualifier_BOC = 1,  //�Է����ż۸�(best of counterparty)
	OrderQualifier_BOP = 2,  //�������ż۸�(best of party)
	OrderQualifier_B5TC = 3,  //�����嵵ʣ�೷��(best 5 then cancel)
	OrderQualifier_B5TL = 4,  //�����嵵ʣ��ת�޼�(best 5 then limit)
};

//�ֲַ���
enum PositionSide
{
	PositionSide_Unknown = 0,
	PositionSide_Long = 1,   //�෽��
	PositionSide_Short = 2,   //�շ���
};

//��ƽ��־
enum PositionEffect
{
	PositionEffect_Unknown = 0,
	PositionEffect_Open = 1,     //����
	PositionEffect_Close = 2,     //ƽ��,��������ȡ���ڶ�Ӧ�Ľ�����
	PositionEffect_CloseToday = 3,     //ƽ���
	PositionEffect_CloseYesterday = 4,     //ƽ���
};

//�ʽ�ֱֲ��ԭ��
enum CashPositionChangeReason
{
	CashPositionChangeReason_Unknown = 0,
	CashPositionChangeReason_Trade = 1,  //����
	CashPositionChangeReason_Inout = 2,  //�����/����ֲ�
	CashPositionChangeReason_Dividend = 3,  //�ֺ��͹�
};

enum AccountState
{
	State_UNKNOWN = 0,       //δ֪
	State_CONNECTING = 1,    //������
	State_CONNECTED = 2,     //������
	State_LOGGEDIN = 3,      //�ѵ�¼
	State_DISCONNECTING = 4, //�Ͽ���
	State_DISCONNECTED = 5,  //�ѶϿ�
	State_ERROR = 6          //����
};

//�㷨��״̬,��ͣ/�ָ��㷨��ʱ��Ч
enum AlgoOrderStatus 
{
	AlgoOrderStatus_Unknown = 0,
	AlgoOrderStatus_Resume = 1,                  //�ָ�ĸ��
	AlgoOrderStatus_Pause = 2,                   //��ͣĸ��
	AlgoOrderStatus_PauseAndCancelSubOrders = 3  //����ĸ�������ӵ�
};

//ͷ����Դ(��������ȯ��ȯ)
enum PositionSrc
{
	PositionSrc_Unknown = 0,
	PositionSrc_L1 = 1,          //��ͨ��
	PositionSrc_L2 = 2           //ר����
};

typedef char Symbol[LEN_SYMBOL];
typedef char TradingDate[LEN_ISO_DATATIME];

struct Bar
{
	char                    symbol[LEN_SYMBOL];
	double                  bob;                          ///bar�Ŀ�ʼʱ��
	double                  eob;                          ///bar�Ľ���ʱ��
	float                   open;                         ///<���̼�
	float                   close;                        ///<���̼�
	float                   high;                         ///<��߼�
	float                   low;                          ///<��ͼ�
	double                  volume;                       ///<�ɽ���
	double                  amount;                       ///<�ɽ����
	float                   pre_close;                    ///�����̼ۣ�ֻ����Ƶ���ݸ�ֵ

	long long               position;                     ///<�ֲ���
	char                    frequency[LEN_FREQUENCY];     ///barƵ��
};

struct Quote
{
	float      bid_price;                            ///����ί���
	long long  bid_volume;                           ///����ί����
	float      ask_price;                            ///����ί����
	long long  ask_volume;                           ///����ί����
};

struct Tick
{
	char                   symbol[LEN_SYMBOL];
	double                 created_at;               ///<utcʱ�䣬��ȷ������
	float                  price;                    ///<���¼�
	float                  open;                     ///<���̼�
	float                  high;                     ///<��߼�
	float                  low;                      ///<��ͼ�
	double                 cum_volume;               ///<�ɽ�����
	double                 cum_amount;               ///<�ɽ��ܽ��/���³ɽ���,�ۼ�ֵ
	long long              cum_position;             ///<��Լ�ֲ���(��),�ۼ�ֵ
	double                 last_amount;              ///<˲ʱ�ɽ���
	int                    last_volume;              ///<˲ʱ�ɽ���
	int                    trade_type;               ///(����)��������,��Ӧ�࿪,��ƽ������
	Quote                  quotes[DEPTH_OF_QUOTE];   ///����, �±��0��ʼ��0-��ʾ��һ����1-��ʾ�ڶ�������������

};

struct L2Transaction
{
	char                   symbol[LEN_SYMBOL];
	double                 created_at;               ///�ɽ�ʱ�䣬utcʱ��
	float                  price;                    ///�ɽ���
	long long              volume;					 ///�ɽ���
	char                   side;                     ///�����̱��
	char                   exec_type;                ///�ɽ�����
};

struct L2Order
{
	char                   symbol[LEN_SYMBOL];
	double                 created_at;               ///ί��ʱ�䣬utcʱ��
	float                  price;                    ///ί�м�
	long long              volume;					 ///ί����
	char                   side;                     ///��������
	char                   order_type;               ///ί������
};

struct L2OrderQueue
{
	char                   symbol[LEN_SYMBOL];
	double                 created_at;                                  ///����ʱ�䣬utcʱ��
	float                  price;                                       ///����ί�м�
	long long              volume;					                    ///ί����
	char                   side;                                        ///��������
	int                    queue_orders;                                ///ί����������Ԫ�ظ���(���50)
	int                    queue_volumes[LEN_MAX_ORDER_QUEUE];          ///ί��������(���50�����п���С��50, ��Ч���ݳ���ȡ����queue_orders)
};


struct Order
{
	char         strategy_id[LEN_ID];                     //����ID                                      
	char         account_id[LEN_ID];                      //�˺�ID                                      
	char         account_name[LEN_NAME];                  //�˻���¼��                                  

	char         cl_ord_id[LEN_ID];                       //ί�пͻ���ID                                
	char         order_id[LEN_ID];                        //ί�й�̨ID                     
	char         ex_ord_id[LEN_ID];                       //ί�н�����ID   
	char         algo_order_id[LEN_ID];                   //�㷨ĸ��ID
	int          order_business;                          //ҵ������

	char         symbol[LEN_SYMBOL];                      //symbol                                      
	int          side;                                    //��������ȡֵ�ο�enum OrderSide            
	int          position_effect;                         //��ƽ��־��ȡֵ�ο�enum PositionEffect       
	int          position_side;                           //�ֲַ���ȡֵ�ο�enum PositionSide         

	int          order_type;                              //ί�����ͣ�ȡֵ�ο�enum OrderType            
	int          order_duration;                          //ί��ʱ�����ԣ�ȡֵ�ο�enum OrderDuration    
	int          order_qualifier;                         //ί�гɽ����ԣ�ȡֵ�ο�enum OrderQualifier   
	int          order_src;                               //ί����Դ��ȡֵ�ο�enum OrderSrc   
	int          position_src;                            //ͷ����Դ��������������ȯ����ȡֵ�ο� enum PositionSrc

	int          status;                                  //ί��״̬��ȡֵ�ο�enum OrderStatus          
	int          ord_rej_reason;                          //ί�оܾ�ԭ��ȡֵ�ο�enum OrderRejectReason
	char         ord_rej_reason_detail[LEN_INFO];         //ί�оܾ�ԭ������                            

	double       price;                                   //ί�м۸�                                    
	double       stop_price;                              //ί��ֹ��/ֹӯ�����۸�                       

	int          order_style;                             //ί�з��ȡֵ�ο� enum OrderStyle          
	long long    volume;                                  //ί����                                      
	double       value;                                   //ί�ж�                                      
	double       percent;                                 //ί�аٷֱ�                                  
	long long    target_volume;                           //ί��Ŀ����                                  
	double       target_value;                            //ί��Ŀ���                                  
	double       target_percent;                          //ί��Ŀ��ٷֱ�                              

	long long    filled_volume;                           //�ѳ���                                      
	double       filled_vwap;                             //�ѳɾ���                                    
	double       filled_amount;                           //�ѳɽ��                                    
	double       filled_commission;                       //�ѳ�������                                  

	long long    created_at;                              //ί�д���ʱ��                                
	long long    updated_at;                              //ί�и���ʱ��  
};

struct AlgoOrder
{
	char         strategy_id[LEN_ID];                     //����ID                                      
	char         account_id[LEN_ID];                      //�˺�ID                                      
	char         account_name[LEN_NAME];                  //�˻���¼��                                  

	char         cl_ord_id[LEN_ID];                       //ί�пͻ���ID                                
	char         order_id[LEN_ID];                        //ί�й�̨ID                                  
	char         ex_ord_id[LEN_ID];                       //ί�н�����ID
	int          order_business;                          //ҵ������

	char         symbol[LEN_SYMBOL];                      //symbol                                      
	int          side;                                    //��������ȡֵ�ο�enum OrderSide            
	int          position_effect;                         //��ƽ��־��ȡֵ�ο�enum PositionEffect       
	int          position_side;                           //�ֲַ���ȡֵ�ο�enum PositionSide         

	int          order_type;                              //ί�����ͣ�ȡֵ�ο�enum OrderType            
	int          order_duration;                          //ί��ʱ�����ԣ�ȡֵ�ο�enum OrderDuration    
	int          order_qualifier;                         //ί�гɽ����ԣ�ȡֵ�ο�enum OrderQualifier   
	int          order_src;                               //ί����Դ��ȡֵ�ο�enum OrderSrc    
	int          position_src;                            //ͷ����Դ��������������ȯ����ȡֵ�ο� enum PositionSrc

	int          status;                                  //ί��״̬��ȡֵ�ο�enum OrderStatus          
	int          ord_rej_reason;                          //ί�оܾ�ԭ��ȡֵ�ο�enum OrderRejectReason
	char         ord_rej_reason_detail[LEN_INFO];         //ί�оܾ�ԭ������                            

	double       price;                                   //ί�м۸�                                    
	double       stop_price;                              //ί��ֹ��/ֹӯ�����۸�                       

	int          order_style;                             //ί�з��ȡֵ�ο� enum OrderStyle          
	long long    volume;                                  //ί����                                      
	double       value;                                   //ί�ж�                                      
	double       percent;                                 //ί�аٷֱ�                                  
	long long    target_volume;                           //ί��Ŀ����                                  
	double       target_value;                            //ί��Ŀ���                                  
	double       target_percent;                          //ί��Ŀ��ٷֱ�                              

	long long    filled_volume;                           //�ѳ���                                      
	double       filled_vwap;                             //�ѳɾ���                                    
	double       filled_amount;                           //�ѳɽ��                                    
	double       filled_commission;                       //�ѳ�������     

	char         algo_name[LEN_NAME];                     //�㷨������
	char         algo_param[LEN_PARAM];                   //�㷨���Բ���
	int          algo_status;                             //�㷨����״̬,����ΪAlgoOrder Pause������Σ�ȡֵ�ο� enum AlgoOrderStatus
	char         algo_comment[LEN_COMMENT];               //�㷨����ע

	long long    created_at;                              //ί�д���ʱ��                                
	long long    updated_at;                              //ί�и���ʱ��  
};

struct AlgoParam 
{
	char              algo_name[LEN_NAME];                 //�㷨����
	char              time_start[LEN_ISO_DATATIME];        //��ʼʱ��
	char              time_end[LEN_ISO_DATATIME];          //����ʱ��
	double            part_rate;                           //���ȱ���
	int               min_amount;                          //��Сί�н��
};

struct ExecRpt
{
	char               strategy_id[LEN_ID];                  //����ID                                                                                                        
	char               account_id[LEN_ID];                   //�˺�ID                                                       
	char               account_name[LEN_NAME];               //�˻���¼��                                                                                                    

	char               cl_ord_id[LEN_ID];                    //ί�пͻ���ID                                                                                                  
	char               order_id[LEN_ID];                     //ί�й�̨ID                                                                                                    
	char               exec_id[LEN_ID];                      //ί�лر�ID                                                                                                    

	char               symbol[LEN_SYMBOL];                   //symbol                                                                                                        

	int                position_effect;                      //��ƽ��־��ȡֵ�ο�enum PositionEffect                                                                         
	int                side;                                 //��������ȡֵ�ο�enum OrderSide                                                                              
	int                ord_rej_reason;                       //ί�оܾ�ԭ��ȡֵ�ο�enum OrderRejectReason                                                                  
	char               ord_rej_reason_detail[LEN_INFO];      //ί�оܾ�ԭ������                                                                                              
	int                exec_type;                            //ִ�лر�����, ȡֵ�ο�enum ExecType                                                                           

	double             price;                                //ί�гɽ��۸�                                                                                                  
	long long          volume;                               //ί�гɽ���                                                                                                    
	double             amount;                               //ί�гɽ����                                                                                                  
	double             commission;                           //ί�гɽ�������                                                                                                
	double             cost;                                 //ί�гɽ��ɱ����  
	long long          created_at;                           //�ر�����ʱ��

};

struct Cash
{
	char          account_id[LEN_ID];                        //�˺�ID               
	char          account_name[LEN_NAME];                    //�˻���¼��                                                                   

	int           currency;                                  //����                                                                         

	double        nav;                                        //��ֵ(cum_inout + cum_pnl + fpnl - cum_commission)                            
	double        pnl;                                        //������(nav-cum_inout)                                                        
	double        fpnl;                                       //����ӯ��(sum(each position fpnl))                                            
	double        frozen;                                     //�ֲ�ռ���ʽ�                                                                 
	double        order_frozen;                               //�ҵ������ʽ�                                                                 
	double        available;                                  //�����ʽ�                                                                     
															  //no  leverage:  available=(cum_inout + cum_pnl - cum_commission - frozen - order_frozen)        
															  //has leverage:  fpnl     =(fpnl>0 ? fpnl : (frozen < |fpnl|) ? (frozen-|fpnl|) : 0)             
															  //               available=(cum_inout + cum_pnl - cum_commission - frozen - order_frozen + fpnl) 
	double        balance;                                    //�ʽ����                                                                     

	double        cum_inout;                                  //�ۼƳ����                                                                   
	double        cum_trade;                                  //�ۼƽ��׶�                                                                   
	double        cum_pnl;                                    //�ۼ�ƽ������(û�۳�������)                                                   
	double        cum_commission;                             //�ۼ�������                                                                   

	double        last_trade;                                 //��һ�ν��׶�                                                                 
	double        last_pnl;                                   //��һ������                                                                   
	double        last_commission;                            //��һ��������                                                                 
	double        last_inout;                                 //��һ�γ����                                                                 
	int           change_reason;                              //�ʽ���ԭ��ȡֵ�ο�enum CashPositionChangeReason                          
	char          change_event_id[LEN_ID];                    //�����ʽ����¼���ID     

	long long     created_at;                                 //�ʽ��ʼʱ��
	long long     updated_at;                                 //�ʽ���ʱ��

};

struct Position
{
	char                 account_id[LEN_ID];              //�˺�ID                                       
	char                 account_name[LEN_NAME];          //�˻���¼��                                                                                       

	char                 symbol[LEN_SYMBOL];              //symbol                                       
	int                  side;                            //�ֲַ���ȡֵ�ο�enum PositionSide          
	long long            volume;                          //�ֲܳ���; ��ֲ���(volume-volume_today)                                                          
	long long            volume_today;                    //���ճֲ���                                                                                       
	double               vwap;                            //�ֲ־���                                                                                         
	double               amount;                          //�ֲֶ�(volume*vwap*multiplier)                                                                   

	double               price;                           //��ǰ����۸�                                                                                     
	double               fpnl;                            //�ֲָ���ӯ��((price-vwap)*volume*multiplier)                                                     
	double               cost;                            //�ֲֳɱ�(vwap*volume*multiplier*margin_ratio)                                                    
	long long            order_frozen;                    //�ҵ������λ                                                                                     
	long long            order_frozen_today;              //�ҵ������ֲ�λ                                                                                 
	long long            available;                       //�����ܲ�λ(volume-order_frozen); �������λ(available-available_today)                           
	long long            available_today;                 //���ý��λ(volume_today-order_frozen_today)
	long long            available_now;                   //��ǰ��ƽ��λ

	double               last_price;                      //��һ�γɽ���                                                                                     
	long long            last_volume;                     //��һ�γɽ���                                                                                     
	long long            last_inout;                      //��һ�γ���ֲ���                                                                                 
	int                  change_reason;                   //��λ���ԭ��ȡֵ�ο�enum CashPositionChangeReason                                              
	char                 change_event_id[LEN_ID];         //�����ʽ����¼���ID                                                                             

	int                  has_dividend;                    //�ֲ������зֺ�����   
	long long            created_at;                      //����ʱ��
	long long            updated_at;                      //��λ���ʱ��

};

struct Account 
{
	char            account_id[LEN_ID];           //�˺�ID
	char            account_name[LEN_NAME];       //�˻���¼��
	char            title[LEN_NAME];              //�˺�����
	char            intro[LEN_INFO];              //�˺�����
	char            comment[LEN_INFO];            //�˺ű�ע
};

struct AccountStatus
{
	char            account_id[LEN_ID];           //�˺�ID
	char            account_name[LEN_NAME];       //�˻���¼��
	int             state;                        //�˻�״̬
	int             error_code;                   //������
	char            error_msg[LEN_INFO];          //������Ϣ
};

struct Parameter
{
	char   key[LEN_ID];          //������
	double value;                //����ֵ
	double min;                  //�����õ���Сֵ
	double max;                  //�����õ����ֵ
	char   name[LEN_NAME];       //������
	char   intro[LEN_INFO];      //����˵��
	char   group[LEN_NAME];      //����
	bool   readonly;             //�Ƿ�ֻ��
};

struct Indicator
{
	char      account_id[LEN_ID];             //�˺�ID
	double    pnl_ratio;                      //�ۼ�������(pnl/cum_inout)
	double    pnl_ratio_annual;               //�껯������
	double    sharp_ratio;                    //���ձ���
	double    max_drawdown;                   //���س�
	double    risk_ratio;                     //���ձ���
	int       open_count;                     //���ִ���
	int       close_count;                    //ƽ�ִ���
	int       win_count;                      //ӯ������
	int       lose_count;                     //�������
	double    win_ratio;                      //ʤ��

	long long  created_at;                    //ָ�괴��ʱ��
	long long  updated_at;                    //ָ����ʱ��
};

struct CollateralInstrument
{
	char                 symbol[LEN_SYMBOL];  //����֤ȯ���
	char                 name[LEN_NAME];      //����
	double               pledge_rate;         //������
};

struct BorrowableInstrument
{
	char                 symbol[LEN_SYMBOL];        //����֤ȯ���
	char                 name[LEN_NAME];            //����
	double               margin_rate_for_cash;      //���ʱ�֤�����
	double               margin_rate_for_security;  //��ȯ��֤�����
};

struct BorrowableInstrumentPosition
{
	char                 symbol[LEN_SYMBOL];        //����֤ȯ���
	char                 name[LEN_NAME];            //����
	double               balance;                   //֤ȯ���
	double               available;                 //֤ȯ����
};

struct CreditContract
{
	char symbol[LEN_SYMBOL];              //֤ȯ���� stkcode    
	char name[LEN_NAME];                  //����
	int orderdate;                        //ί������                   
	char ordersno[LEN_ID];                //ί �� ��                   
	char creditdirect;                    //������ȯ����               
	double orderqty;                      //ί������                   
	double matchqty;                      //�ɽ�����                   
	double orderamt;                      //ί�н��                   
	double orderfrzamt;                   //ί�ж�����               
	double matchamt;                      //�ɽ����                   
	double clearamt;                      //������                   
	char lifestatus;                      //��Լ״̬                   
	int enddate;                          //��ծ��ֹ����               
	int oldenddate;                       //ԭʼ�ĸ�ծ��ֹ����         
	double creditrepay;                   //T��֮ǰ�黹���            
	double creditrepayunfrz;              //T�չ黹���                
	double fundremain;                    //Ӧ�����                   
	double stkrepay;                      //T��֮ǰ�黹����            
	double stkrepayunfrz;                 //T�չ黹����                
	double stkremain;                     //Ӧ��֤ȯ����               
	double stkremainvalue;                //Ӧ��֤ȯ��ֵ               
	double fee;                           //������ȯϢ����             
	double overduefee;                    //����δ����Ϣ����           
	double fee_repay;                     //������Ϣ����               
	double punifee;                       //��Ϣ�����ķ�Ϣ             
	double punifee_repay;                 //��������Ϣ                 
	double rights;                        //δ����Ȩ����             
	double overduerights;                 //����δ����Ȩ��             
	double rights_repay;                  //������Ȩ��                 
	double lastprice;                     //���¼�                     
	double profitcost;                    //����ӯ��                   
	int sysdate;                          //ϵͳ����                   
	char sno[LEN_ID];                     //��Լ���                   
	int lastdate;                         //���һ�μ���Ϣ������       
	int closedate;                        //��Լȫ����������           
	double punidebts;                     //���ڱ���Ϣ               
	double punidebts_repay;               //����Ϣ����               
	double punidebtsunfrz;                //���ڱ���Ϣ               
	double punifeeunfrz;                  //����Ϣ�ѷ�Ϣ               
	double punirights;                    //����Ȩ�淣Ϣ               
	double punirights_repay;              //Ȩ�淣Ϣ����               
	double punirightsunfrz;               //����Ȩ�淣Ϣ               
	double feeunfrz;                      //ʵʱ������Ϣ               
	double overduefeeunfrz;               //ʵʱ����������Ϣ           
	double rightsqty;                     //δ����Ȩ������             
	double overduerightsqty;              //����δ����Ȩ������    
};


struct CreditCash
{
	double fundintrrate;                        //��������                 
	double stkintrrate;                         //��ȯ����                 
	double punishintrrate;                      //��Ϣ����                 
	char   creditstatus;                        //����״̬                 
	double marginrates;                         //ά�ֵ�������             
	double realrate;                            //ʵʱ��������             
	double asset;                               //���ʲ�                   
	double liability;                           //�ܸ�ծ                   
	double marginavl;                           //��֤�������             
	double fundbal;                             //�ʽ����                 
	double fundavl;                             //�ʽ������               
	double dsaleamtbal;                         //��ȯ���������ʽ�         
	double guaranteeout;                        //��ת�������ʲ�           
	double gagemktavl;                          //����֤ȯ��ֵ             
	double fdealavl;                            //���ʱ���                 
	double ffee;                                //����Ϣ��                 
	double ftotaldebts;                         //���ʸ�ծ�ϼ�             
	double dealfmktavl;                         //Ӧ����ȯ��ֵ             
	double dfee;                                //��ȯϢ��                 
	double dtotaldebts;                         //��ȯ��ծ�ϼ�             
	double fcreditbal;                          //�������Ŷ��             
	double fcreditavl;                          //���ʿ��ö��             
	double fcreditfrz;                          //���ʶ�ȶ���             
	double dcreditbal;                          //��ȯ���Ŷ��             
	double dcreditavl;                          //��ȯ���ö��             
	double dcreditfrz;                          //��ȯ��ȶ���             
	double rights;                              //����Ȩ��                 
	double serviceuncomerqrights;               //����Ȩ��(��;)           
	double rightsqty;                           //���Ȩ��                 
	double serviceuncomerqrightsqty;            //���Ȩ��(��;)           
	double acreditbal;                          //�ܶ��                   
	double acreditavl;                          //�ܿ��ö��               
	double acashcapital;                        //�����ֽ��ʲ��������ʲ���������ȯ������     
	double astkmktvalue;                        //����֤ȯ��ֵ�������������롢�ǵ���Ʒ��     
	double withdrawable;                        //��ȡ�ʽ�                                   
	double netcapital;                          //���ʲ�                                     
	double fcreditpnl;                          //����ӯ��                                   
	double dcreditpnl;                          //��ȯӯ��                                   
	double fcreditmarginoccupied;               //����ռ�ñ�֤��                             
	double dcreditmarginoccupied;               //��ȯռ�ñ�֤��                             
	double collateralbuyableamt;                //���򵣱�Ʒ�ʽ�                             
	double repayableamt;                        //�ɻ�����                                 
	double dcreditcashavl;                      //��ȯ�����ʽ�     
};

struct IPOInstruments
{
	char     symbol[LEN_SYMBOL];     //�깺�¹�symbol
	double   price;                  //�깺�۸�
	int      min_vol;                //�깺��С����
	int      max_vol;                //�깺�������
};

struct IPOMatchNumber
{
	char order_id[LEN_ID];           //ί�к�
	char symbol[LEN_SYMBOL];         //�¹�symbol
	int   volume;                    //�ɽ�����
	char match_number[LEN_ID];       //�깺���
	int  order_at;                   //ί������
	int  match_at;                    //�������
};

struct IPOLotInfo
{
	char symbol[LEN_SYMBOL];   //�¹�symbol   
	int order_at;              //ί������     
	int lot_at;                //��ǩ����     
	int lot_volume;            //��ǩ����     
	int give_up_volume;        //��������     
	double price;              //��ǩ�۸�     
	double amount;             //��ǩ���     
	double pay_volume;         //�ѽɿ�����   
	double pay_amount;         //�ѽɿ���   

};

#endif
