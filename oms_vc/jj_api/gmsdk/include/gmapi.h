#ifndef GMCPPSDK_H
#define GMCPPSDK_H

#include <iostream>
#include "gmdef.h"

#ifdef WIN32
#ifdef GMSDKC_EXPORTS  
#define GM_CXX_API __declspec(dllexport)
#else
#define GM_CXX_API __declspec(dllimport)
#endif
#else
#define GM_CXX_API
#endif

//�������
class DataSet
{
public:
	//��ȡapi���ý��, 0: �ɹ��� ��0: ������
	virtual int status() = 0;

	//�ж��Ƿ��Ѿ��ǵ�������ĩβ
	virtual bool is_end() = 0;

	//�Ƶ���һ����¼
	virtual void next() = 0;

	//��ȡ����ֵ
	virtual int get_integer(const char *key) = 0;

	//��ȡ������ֵ
	virtual long long get_long_integer(const char *key) = 0;

	//��ȡ������ֵ
	virtual double get_real(const char *key) = 0;

	//��ȡ�ַ�����ֵ
	virtual const char* get_string(const char *key) = 0;

	//�ͷ����ݼ���
	virtual void release() = 0;

	//��ӡ����
	virtual const char* debug_string() = 0;
};

//�������
template <typename T>
class DataArray
{
public:
	//��ȡapi���ý��, 0: �ɹ��� ��0: ������
	virtual int status() = 0;

	//���ؽṹ�����ָ��
	virtual T* data() = 0;

	//�������ݵĳ���
	virtual int count() = 0;

	//�����±�Ϊi�Ľṹ���ã���0��ʼ
	virtual T& at(int i) = 0;

	//�ͷ����ݼ���
	virtual void release() = 0;
};

// ��ȡsdk�汾��
GM_CXX_API const char* get_version();

// ����token
GM_CXX_API void set_token(const char *token);

// �Զ�������ַ
GM_CXX_API void set_serv_addr(const char *addr);

//������ϵͳ����������Ϣ
GM_CXX_API void set_mfp(const char *mfp);

// ��ѯ��ǰ�������
GM_CXX_API DataArray<Tick>* current(const char *symbols);

// ��ѯ��ʷTick����
GM_CXX_API DataArray<Tick>* history_ticks(const char *symbols, const char *start_time, const char *end_time, int adjust = 0, const char *adjust_end_time = NULL, bool skip_suspended = true, const char *fill_missing = NULL);

// ��ѯ��ʷBar����
GM_CXX_API DataArray<Bar>* history_bars(const char *symbols, const char *frequency, const char *start_time, const char *end_time, int adjust = 0, const char *adjust_end_time = NULL, bool skip_suspended = true, const char *fill_missing = NULL);

// ��ѯ����n��Tick����
GM_CXX_API DataArray<Tick>* history_ticks_n(const char *symbols, int n, const char *end_time = NULL, int adjust = 0, const char *adjust_end_time = NULL, bool skip_suspended = true, const char *fill_missing = NULL);

//��ѯ����n��Bar����
GM_CXX_API DataArray<Bar>* history_bars_n(const char *symbols, const char *frequency, int n, const char *end_time = NULL, int adjust = 0, const char *adjust_end_time = NULL, bool skip_suspended = true, const char *fill_missing = NULL);

// ��ѯ��ʷL2 Tick����
GM_CXX_API DataArray<Tick>* history_l2ticks(const char *symbols, const char *start_time, const char *end_time, int adjust = 0, const char *adjust_end_time = NULL, bool skip_suspended = true, const char *fill_missing = NULL);

// ��ѯ��ʷL2 Bar����
GM_CXX_API DataArray<Bar>* history_l2bars(const char *symbols, const char *frequency, const char *start_time, const char *end_time, int adjust = 0, const char *adjust_end_time = NULL, bool skip_suspended = true, const char *fill_missing = NULL);

// ��ѯ��ʷL2 ��ʳɽ�
GM_CXX_API DataArray<L2Transaction>* history_l2transactions(const char *symbols, const char *start_time, const char *end_time);

// ��ѯ��ʷL2 ���ί��
GM_CXX_API DataArray<L2Order>* history_l2orders(const char *symbols, const char *start_time, const char *end_time);

// ��ѯ��ʷL2 ί�ж���(���ż����50��ί����)
GM_CXX_API DataArray<L2OrderQueue>* history_l2orders_queue(const char *symbols, const char *start_time, const char *end_time);

// ��ѯ����������
GM_CXX_API DataSet* get_fundamentals(const char *table, const char *symbols, const char *start_date, const char *end_date, const char *fields, const char *filter = NULL, const char *order_by = NULL, int limit = 1000);

// ��ѯ��������������n��
GM_CXX_API DataSet* get_fundamentals_n(const char *table, const char *symbols, const char *end_date, const char *fields, int n = 1, const char *filter = NULL, const char * order_by = NULL);

// ��ѯ���½��ױ����Ϣ
GM_CXX_API DataSet* get_instruments(const char *exchanges = NULL, const char *sec_types = NULL, const char* fields = NULL);

// ��ѯ���ױ����ʷ����
GM_CXX_API DataSet* get_history_instruments(const char *symbols, const char *start_date, const char *end_date, const char *fields = NULL);

// ��ѯ���ױ�Ļ�����Ϣ
GM_CXX_API DataSet* get_instrumentinfos(const char *symbols = NULL, const char *exchanges = NULL, const char * sec_types = NULL, const char *names = NULL, const char *fields = NULL);

// ��ѯָ���ɷݹ�
GM_CXX_API DataSet* get_constituents(const char *index, const char *trade_date = NULL);

// ��ѯ��ҵ��Ʊ�б�
GM_CXX_API DataArray<Symbol>* get_industry(const char *code);

// ��ѯ�������Ʊ�б�
GM_CXX_API DataArray<Symbol>* get_concept(const char *code);

// ��ѯ�������б�
GM_CXX_API DataArray<TradingDate>* get_trading_dates(const char *exchange, const char *start_date, const char *end_date);

// ����ָ�����ڵ���һ��������
GM_CXX_API int get_previous_trading_date(const char *exchange, const char *date, char *output_date);

// ����ָ�����ڵ���һ��������
GM_CXX_API int get_next_trading_date(const char *exchange, const char *date, char *output_date);

// ��ѯ�ֺ�����
GM_CXX_API DataSet* get_dividend(const char *symbol, const char *start_date, const char *end_date);

// ��ȡ������Լ
GM_CXX_API DataSet* get_continuous_contracts(const char *csymbol, const char *start_date, const char *end_date);


#endif
