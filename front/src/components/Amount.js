import React from 'react';

const Amount = (props) => {
  const { amount, onChange, onClick } = props;
  return (
    <>
      <div className='amount-box'>
        <span className='amount-sale'>Sale amount</span>
        <div className='amount-text-container'>
          <span className='amount-text' onChange={onChange}>
            ${amount}
          </span>
          {amount && (
            <button className='amount-delete-btn' onClick={onClick}>
              <i className='fa-solid fa-circle-xmark amount-delete-icon'></i>
            </button>
          )}
        </div>
      </div>
    </>
  );
};
export default Amount;
